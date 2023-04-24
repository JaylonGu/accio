// SPDX-License-Identifier: MIT
pragma solidity >=0.8.0;

import "./pairing.sol";

contract Hub {
   event Open(address indexed P, address indexed Q, uint balance);
   event Close(uint balP, uint balQ, string st);

   enum Status{open,closing,closed}

   struct ST{
      uint bal;
      Pairing.Commitment cm;
      Pairing.Signature sigma_hat;
      uint128 v;
      uint r;
      bytes sig;
   }

   Status   _st = Status.closed;
   address  _userP;    
   address  _userQ;    
   uint8    _types;
   uint     _timeout;
   Pairing.Vk  _vk;

   // constructor (){
   //    _userP = msg.sender;
   //    _userQ = msg.sender;
   //    _types = 0;
   //    _timeout = 0;
   //    _vk = Pairing.Vk(Pairing.G_hat(),Pairing.G_hat());
   // }

   constructor (){
      _userP = msg.sender;
      _userQ = msg.sender;
      _types = 1;
      _timeout = 0;
      _vk = Pairing.Vk(Pairing.G_hat(),Pairing.G_hat());
   }

   // 恢复出hash和对应签名的地址
   function recover(bytes32 hash, bytes memory signature) internal pure returns (address) {
         bytes32 r;
         bytes32 s;
         uint8 v;

         assembly {
               r := mload(add(signature, 0x20))
               s := mload(add(signature, 0x40))
               v := byte(0, mload(add(signature, 0x60)))
         }
         return ecrecover(hash, v, r, s);
   }

   function sigverify(bytes memory _signature, bytes memory m)
         internal view
         returns (bool)
   {
      bytes32 messagehash = keccak256(m);
      address signer = recover(messagehash, _signature);

      if (_userP == signer) {
            return true;
      } else {
            return false;
      }
   }
   

   function verify(ST memory st) internal view returns (bool){
      if(_types == 0){
         bytes memory message = abi.encode(st.bal, st.v, st.cm.c0.X,st.cm.c0.Y,st.cm.c1.X,st.cm.c1.Y,address(this));
         bool b2 = sigverify(st.sig, message);
         Pairing.Commitment memory cm_new = Pairing.cHomo(st.cm, st.v);
         bool b3 = Pairing.cVf(cm_new, st.sigma_hat, _vk);
         return st.bal>=0 && st.bal<= address(this).balance && st.v>=0 && b2 && b3;
      }else{
         uint bal = address(this).balance - st.bal;
         Curve.G1Point memory p = Curve.g1mul(Pairing.G(), ((( uint256(keccak256(  abi.encodePacked(address(this))  )) >> 128 ) << 131) >> 3)+bal); 
         bool b1 = Pairing.cOpen(st.cm, p, st.r);
         bool b2 = Pairing.cVf(st.cm, st.sigma_hat, _vk);
         return st.bal>=0 && st.bal<= address(this).balance && b1 && b2;      
      }
   }


// vk [[["11559732032986387107991004021392285783925812861821192530917403151452391805634","10857046999023057135944570762232829481370756359578518086990519993285655852781"],["4082367875863433681332203403145435568316851327593401208105741076214120093531","8495653923123431417604973247489272438418190587263600148770280649306958101930"]],[["11559732032986387107991004021392285783925812861821192530917403151452391805634","10857046999023057135944570762232829481370756359578518086990519993285655852781"],["4082367875863433681332203403145435568316851327593401208105741076214120093531","8495653923123431417604973247489272438418190587263600148770280649306958101930"]]]
// msg.value 1Ether

   // function open(uint8 types, Pairing.Vk memory vk, address Q) public payable{  // invoke channel opening     
   //    require(_st == Status.closed);
   //    _st = Status.open;
   //    _types = types;
   //    _userP = msg.sender;
   //    _userQ = Q;
   //    _vk = vk;
   //    // _fund = msg.value;
   //    payable(address(this)).transfer(msg.value);
   //    // emit Open(_userP, _userQ, address(this).balance);
   // }

   function open(uint8 types, Pairing.Vk memory vk, address Q) public payable{  // invoke channel opening     
      require(_st == Status.closed && _userP == msg.sender);
      _st = Status.open;
      _types = types;
      _userQ = Q;
      _vk = vk;
      // _fund = msg.value;
      payable(address(this)).transfer(msg.value);
      // emit Open(_userP, _userQ, address(this).balance);
   }

   // function open(address Q) public payable{  // invoke channel opening     
   //    require(_st == Status.closed);
   //    _st = Status.open;
   //    _userP = msg.sender;
   //    _userQ = Q;
   //    // _vk = vk;
   //    payable(address(this)).transfer(msg.value);
   // }

   function close(ST memory st) public { // invoke channel closing
      require(_st == Status.open);
      require(msg.sender == _userP || msg.sender == _userQ);

      if(msg.sender == _userP){  // if msg.sender is sender
         _st = Status.closing;
         if(_types == 0){
            _timeout = block.timestamp + 20 minutes;
            // _timeout = block.timestamp + 0 minutes;
         }else{
            _timeout = block.timestamp + 60 minutes;
            // _timeout = block.timestamp + 0 minutes;
         }
      }else if(msg.sender == _userQ){  // if msg.sender is receiver
         if(verify(st)){
            emit Close( st.bal,address(this).balance-st.bal, "verified");
            payable(_userQ).transfer(address(this).balance-st.bal);
            payable(_userP).transfer(st.bal);
            _st = Status.closed;
         }else{
            emit Close(address(this).balance, 0, "not verified");
            payable(_userP).transfer(address(this).balance);
            _st = Status.closed;
         }
      }
   }

   function close_resp(ST memory st) public{
      require(_st == Status.closing && msg.sender == _userQ);
      require(block.timestamp <= _timeout);
      if(verify(st)){
            emit Close(st.bal, address(this).balance-st.bal, "verified");
            payable(_userQ).transfer(address(this).balance-st.bal);
            payable(_userP).transfer(st.bal);
            _st = Status.closed;
         }else{
            emit Close(address(this).balance, 0, "not verified");
            payable(_userP).transfer(address(this).balance);
            _st = Status.closed;
      }
   }

   function close_timeout() public{
      require(_st == Status.closing && msg.sender == _userP && block.timestamp > _timeout);
      emit Close(address(this).balance, 0, "not verified");
      payable(_userP).transfer(address(this).balance);
      _st = Status.closed;
   }

   receive() external payable {}

   // function getBalance() public view returns (uint) {
   //    return address(this).balance;
   // }

   // function returnBalance() public {
   //    payable(_userP).transfer(address(this).balance);
   // }
}