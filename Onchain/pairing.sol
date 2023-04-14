// SPDX-License-Identifier: MIT
pragma solidity >=0.8.15;

import "./altbn128.sol";
import "./BN256G2.sol";

library Pairing {
   	struct Sk{
		uint256 x0;
		uint256 x1;
	}

	struct Vk{
		Curve.G2Point x0;
		Curve.G2Point x1;
	}

	struct Commitment{
		Curve.G1Point c0;
		Curve.G1Point c1;
	}

	struct Signature{
		Curve.G1Point Z;
		Curve.G1Point S;
		Curve.G2Point S_hat;
		Curve.G1Point T;
	}

	// uint256 internal p = Curve.P();
	uint256 internal constant q = 0x30644e72e131a029b85045b68181585d2833e84879b9709143e1f593f0000001;
	function G() pure internal returns (Curve.G1Point memory) {
		return Curve.G1Point(1, 2);
	}

	function P() pure public returns (Curve.G1Point memory) {
		return Curve.G1Point(1368015179489954701390400359078579693043519447331113978918064868415326638035,9918110051302171585080402603319702774565515993150576347155970296011118125764);
	}

	function G_hat() pure internal returns (Curve.G2Point memory) {
		return Curve.G2Point(
			[11559732032986387107991004021392285783925812861821192530917403151452391805634,
			 10857046999023057135944570762232829481370756359578518086990519993285655852781],
			[4082367875863433681332203403145435568316851327593401208105741076214120093531,
			 8495653923123431417604973247489272438418190587263600148770280649306958101930]
		);
	}

	function sk() pure internal returns (Sk memory){
		return Sk(1, 1);
	}

	function vk() pure internal returns (Vk memory){
		return Vk(G_hat(),G_hat());
	}

	// function vk() view internal returns (Vk memory){
	// 	return Vk(g2mul(G_hat(),sk().x0),g2mul(G_hat(),sk().x1));
	// }

	function g1eq(Curve.G1Point memory p1, Curve.G1Point memory p2) private pure returns (bool){
		if(p1.X == p2.X && p1.Y == p2.Y){
			return true;
		}else return false;
	}

	function g2add(Curve.G2Point memory p1, Curve.G2Point memory p2) view internal returns (Curve.G2Point memory){
		uint256 xx;
		uint256 xy;
		uint256 yx;
		uint256 yy;
		(xx,xy,yx,yy)= BN256G2.ECTwistAdd(p1.X[1],p1.X[0],p1.Y[1],p1.Y[0],p2.X[1],p2.X[0],p2.Y[1],p2.Y[0]);
		return Curve.G2Point([xy,xx],[yy,yx]);
	}

	function g2mul(Curve.G2Point memory _p, uint s) view internal returns (Curve.G2Point memory){
		uint256 xx;
		uint256 xy;
		uint256 yx;
		uint256 yy;
		(xx,xy,yx,yy)= BN256G2.ECTwistMul(s,_p.X[1],_p.X[0],_p.Y[1],_p.Y[0]);
		return Curve.G2Point([xy,xx],[yy,yx]);
	}

	// function modinverse (uint256 x) view internal returns (uint256){
	// 	return Curve.expMod(x,q-2,q);
	// }

	// Sk public sk = Sk(uint(keccak256("r1"))%p, uint(keccak256("r2"))%p);

	// Vk public vk = Vk(g2mul(G_hat,sk.x0),g2mul(G_hat,sk.x1));

	// function commit(Curve.G1Point memory m) public view returns (Commitment memory, uint256){
	// 	// uint256 r = uint(keccak256("r3")) % p;
	// 	uint256 r = 1;
	// 	Commitment memory c = Commitment(Curve.g1mul(G(),r), Curve.g1add(Curve.g1mul(P(),r),m) );
	// 	return (c,r);
	// }

	function cHomo(Commitment memory c, uint a) internal view returns (Commitment memory){
		Curve.G1Point memory p = Curve.g1mul(G(),a);
		// return G();
		return Commitment(c.c0, Curve.g1add(c.c1, p));
	}

	// function cHomo(Curve.G1Point memory c0, Curve.G1Point memory c1, uint a) internal view returns (Curve.G1Point memory){
	// 	// Curve.G1Point memory p = Curve.g1mul(G(),a);
	// 	return G();
	// 	// return Commitment(c.c0, Curve.g1add(c.c1, p));
	// }
	
	function cOpen(Commitment memory c, Curve.G1Point memory m, uint256 r) public view returns (bool){
		if(g1eq(c.c0,Curve.g1mul(G(),r)) && g1eq(c.c1,Curve.g1add(m,Curve.g1mul(P(),r)))){
			return true;
		}else return false;
	}

	// function cSign(Commitment memory c, Sk memory _sk) public view returns (Signature memory){
	// 	uint s = 2;

	// 	Curve.G1Point memory Z = Curve.g1mul(Curve.g1add(Curve.g1add(G(),Curve.g1mul(c.c0,_sk.x0)), Curve.g1mul(c.c1,_sk.x1)), BN256G2._modInv(s,q));
	// 	// Curve.G1Point memory Z = Curve.g1mul(Curve.g1add(Curve.g1add(G,Curve.g1mul(c.c0,_sk.x0)), Curve.g1mul(c.c1,_sk.x1)), modinverse(s));
	// 	Curve.G1Point memory S = Curve.g1mul(G(),s);
	// 	Curve.G2Point memory S_hat = g2mul(G_hat(),s);
	// 	Curve.G1Point memory T = Curve.g1mul(Curve.g1add(Curve.g1mul(G(),_sk.x0),Curve.g1mul(P(),_sk.x1)), BN256G2._modInv(s,q));
	// 	// Curve.G1Point memory T = Curve.g1mul(Curve.g1add(Curve.g1mul(G,_sk.x0),Curve.g1mul(P,_sk.x1)), modinverse(s));

	// 	Signature memory sigma = Signature(Z,S,S_hat,T);
	// 	return sigma;
	// }

	function cVf(Commitment memory c, Signature memory sigma, Vk memory _vk) public view returns (bool){
		if(sigma.S.X == 0 && sigma.S.Y == 0 ) return false;
		bool pair1 = Curve.pairingProd4(G(), G_hat(), c.c0, _vk.x0, c.c1, _vk.x1, Curve.g1neg(sigma.Z), sigma.S_hat);
		bool pair2 = Curve.pairingProd2(sigma.S, G_hat(), Curve.g1neg(G()), sigma.S_hat);
		bool pair3 = Curve.pairingProd3(G(), _vk.x0, P(), _vk.x1, Curve.g1neg(sigma.T), sigma.S_hat);

		return pair1 && pair2 && pair3;
	}

	// function cRdm(Commitment memory c, Signature memory sigma) public view returns (Commitment memory, Signature memory){
	// 	uint r_ = uint(keccak256("r5"))%q;
	// 	uint s_ = uint(keccak256("r6"))%q;

	// 	Commitment memory c_ = Commitment(Curve.g1add(c.c0,Curve.g1mul(G(),r_)), Curve.g1add(c.c1, Curve.g1mul(P(),r_)));

	// 	Curve.G1Point memory Z_ = Curve.g1mul(Curve.g1add(sigma.Z, Curve.g1mul(sigma.T, r_)), BN256G2._modInv(s_,q));
	// 	Curve.G1Point memory S_ = Curve.g1mul(sigma.S,s_);
	// 	Curve.G2Point memory S_hat_ = g2mul(sigma.S_hat,s_);
	// 	Curve.G1Point memory T_ = Curve.g1mul(sigma.T ,BN256G2._modInv(s_,q));

	// 	Signature memory sigma_ = Signature(Z_,S_,S_hat_,T_);
	// 	return (c_, sigma_);
	// }
}