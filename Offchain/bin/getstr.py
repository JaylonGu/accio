import subprocess

res = subprocess.check_output('./main', shell=True)
res = res.decode('utf-8')
r = res.splitlines()

# print(r)

cm00 = r[1].split()
cm01 = r[2].split()
sz = r[3].split()
ss = r[4].split()
ssh = r[5].split()
st = r[6].split()

cm10 = r[10].split()
cm11 = r[11].split()
# sig_hat: z,s,s_hat,t
sz1 = r[12].split()
ss1 = r[13].split()
ssh1 = r[14].split()
st1 = r[15].split()

#       bal            cm                           sig_hat                                              v   r   sig
print('["{}",[["{}","{}"],["{}","{}"]],[["{}","{}"],["{}","{}"],[["{}","{}"],["{}","{}"]],["{}","{}"]],"{}","0","0x{}"]'.format(r[0],cm00[1],cm00[2],cm01[1],cm01[2],sz[1],sz[2],ss[1],ss[2],ssh[2],ssh[1],ssh[4],ssh[3],st[1],st[2],r[7],r[8]))
print('["{}",[["{}","{}"],["{}","{}"]],[["{}","{}"],["{}","{}"],[["{}","{}"],["{}","{}"]],["{}","{}"]],"0","{}","0"]'.format(r[9],cm10[1],cm10[2],cm11[1],cm11[2],sz1[1],sz1[2],ss1[1],ss1[2],ssh1[2],ssh1[1],ssh1[4],ssh1[3],st1[1],st1[2],r[16]))