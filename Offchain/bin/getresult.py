import subprocess
import numpy as np

payer = np.zeros(100)
tumbler = np.zeros(100)
init = np.zeros(100)
payee = np.zeros(100)
checkinit = np.zeros(100)

for i in range(100):
    res = subprocess.check_output('./main', shell=True)
    res = res.decode('utf-8')
    res_split = res.splitlines()

    init_time = eval(res_split[1][-11:-4])
    checkinit_time = eval(res_split[4][-11:-4])
    pay_time = eval(res_split[7][-11:-4])
    update_time = eval(res_split[10][-11:-4])
    updateconfirm_time = eval(res_split[14][-11:-4])
    checkupdate_time = eval(res_split[18][-11:-4])
    checkpay_time = eval(res_split[21][-11:-4])

    payer[i] = update_time + checkupdate_time
    tumbler[i] = updateconfirm_time
    init[i] = init_time
    payee[i] = pay_time + checkpay_time
    checkinit[i] = checkinit_time

print("\n","="*10, "Our Performance", "="*10, "\n")
print("payer update average time: {:.5f} sec".format(np.mean(payer)))
print("tumbler init average time: {:.5f} sec".format(np.mean(init)))
print("tumbler updateconfirm average time: {:.5f} sec".format(np.mean(tumbler)))
print("payee checkinit time: {:.5f} sec".format(np.mean(checkinit)))
print("payee pay average time: {:.5f} sec\n".format(np.mean(payee)))
