#include "types.h"
#include "util.h"
#include "payer.h"
#include "payee.h"
#include "tumbler.h"
#include <time.h>


// 把十六进制数字数组转换成字符串
void hextoString(const unsigned char* hex, unsigned char *str, int hexlen){
    unsigned char left;
    unsigned char right;

    for(int i = 0; i < hexlen; ++i){
        int j = 2 * i;
        left = hex[i] >> 4;
        right = hex[i] & 0xf;
        if(left>=0x00 && left <= 0x09){
            str[j] = left + 0x30;
        }else{
            str[j] = left + 'a' - 0xa;
        }
        if(right>=0x00 && right <= 0x09){
            str[j+1] = right + 0x30;
        }else{
            str[j+1] = right + 'a' - 0xa;
        }
        // printf("%c%c",str[j],str[j+1]);
    }
    // printf("\n");
}
char id_0[20], id_1[20];

int main(int argc, char const *argv[])
{
    long long start_time, stop_time, total_time;
    // long long total_time_pay1, total_time_pay2, total_time_update1, total_time_update2;
    init();

    // 这里的id为合约地址
    char id_1_str[43], id_0_str[43];
    // printf("Input type 0 contract address (start with 0x): \n");
    scanf("%s", id_0_str);
    for (int i = 0; i < 40; i += 2)
    {
        char slice[3]={0};
        slice[0] = id_0_str[i+2] ;
        slice[1] = id_0_str[i+3];
        sscanf(slice, "%hhx", id_0 + i / 2);
    }
    // printf("Input type 1 contract address (start with 0x): \n");
    scanf("%s", id_1_str);
    for (int i = 0; i < 40; i += 2)
    {
        char slice[3]={0};
        slice[0] = id_1_str[i+2] ;
        slice[1] = id_1_str[i+3];
        sscanf(slice, "%hhx", id_1 + i / 2);
    }

    //tumbler send message to payee
    start_time = ttimer();

    initialize(id_1);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("Initialize time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // payee 
    start_time = ttimer();
    checkInitial(cm_1, &r_1, sig_hat_1);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("CheckInitial time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

        // send message to payer， 收款10000
    start_time = ttimer();
    pay("10000");
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("Pay time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // payer send message to tumbler
    start_time = ttimer();
    // receive hidden state from payee
    update("10000", cm_1, sig_hat_1);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("Update time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // tumbler send message to payer
    start_time = ttimer();
    // receive msg and ecsig of msg, sighat of payee
    updateConfirm(&bal_s_tmp, &amt, cm_1, sig_0, sig_hat_1);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("UpdateConfirm time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // payer send message to payee
    start_time = ttimer();
    checkUpdate(cm_0, sig_hat_0);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("CheckUpdate time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // payee
    start_time = ttimer();
    checkPay(cm_0, sig_hat_0);
    stop_time = ttimer();
    total_time = stop_time - start_time;
    // printf("CheckPay time: %.5f sec\n\n", total_time / CLOCK_PRECISION);

    // char cm_0_c0_x[257], cm_0_c0_y[257], cm_0_c1_x[257], cm_0_c1_y[257];
    // char sig_0_z_x[257], sig_0_z_y[257], sig_0_s_x[257], sig_0_s_y[257], sig_0_sh_x1[257], \
    // sig_0_sh_x2[257], sig_0_sh_y1[257], sig_0_sh_y2[257], sig_0_t_x[257], sig_0_t_y[257];


    // mclBnFp_getStr(cm_0_c0_x, 257, &((cm_0_old->c0).x), 10);
    // mclBnFp_getStr(cm_0_c0_y, 257, &((cm_0_old->c0).y), 10);
    // mclBnFp_getStr(cm_0_c1_x, 257, &((cm_0_old->c1).x), 10);
    // mclBnFp_getStr(cm_0_c1_y, 257, &((cm_0_old->c1).y), 10);

    // mclBnFp_getStr(sig_0_z_x, 257, &((sig_hat_0->z).x), 10);    
    // mclBnFp_getStr(sig_0_z_y, 257, &((sig_hat_0->z).y), 10);   
    // mclBnFp_getStr(sig_0_s_x, 257, &((sig_hat_0->s).x), 10);    
    // mclBnFp_getStr(sig_0_s_y, 257, &((sig_hat_0->s).y), 10);   
    // mclBnFp_getStr(sig_0_t_x, 257, &((sig_hat_0->t).x), 10);    
    // mclBnFp_getStr(sig_0_t_y, 257, &((sig_hat_0->t).y), 10);

    // mclBnFp_getStr(sig_0_sh_x1, 257, &((sig_hat_0->s_hat).x.d[0]), 10);    
    // mclBnFp_getStr(sig_0_sh_x2, 257, &((sig_hat_0->s_hat).x.d[1]), 10);   
    // mclBnFp_getStr(sig_0_sh_y1, 257, &((sig_hat_0->s_hat).y.d[0]), 10);    
    // mclBnFp_getStr(sig_0_sh_y2, 257, &((sig_hat_0->s_hat).y.d[1]), 10);


    // printf("Cm valid: %d, %d\n",mclBnG1_isValid(&(cm_0_old->c0)), mclBnG1_isValid(&(cm_0_old->c1)));
    // mclBnG1 p;
    // char buf[1000];
    // mclBnG1_getStr(buf,1000,&(cm_0_old->c0),10);
    // printf("c.c0: %s\n", buf);
    char bal_s_str[257];
    char c0_c0[1000], c0_c1[1000];
    char sig_0_z[1000], sig_0_s[1000], sig_0_sh[1000], sig_0_t[1000];
    char amt_str[257];
    char r1_str[257];
    unsigned char sig_str[257]={0};

    mclBnFr_getStr(bal_s_str, 257, &bal_s, 10);

    mclBnG1_getStr(c0_c0, 1000, &(cm_0_old->c0), 10);
    mclBnG1_getStr(c0_c1, 1000, &(cm_0_old->c1), 10);

    mclBnG1_getStr(sig_0_z, 1000, &(sig_hat_0->z), 10);
    mclBnG1_getStr(sig_0_s, 1000, &(sig_hat_0->s), 10);
    mclBnG2_getStr(sig_0_sh, 1000, &(sig_hat_0->s_hat), 10);
    mclBnG1_getStr(sig_0_t, 1000, &(sig_hat_0->t), 10);

    mclBnFr_getStr(amt_str, 257, &amt, 10);

    mclBnFr_getStr(r1_str, 257, &r_1, 10);

    hextoString(sig_0_cpt, sig_str, 65);

    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",bal_s_str, c0_c0,c0_c1,sig_0_z,sig_0_s,sig_0_sh,sig_0_t,amt_str,sig_str);

    // printf("ST0:\n");
    // printf("[\"%s\",[[\"%s\",\"%s\"],[\"%s\",\"%s\"]],[[\"%s\",\"%s\"],[\"%s\",\"%s\"],[[\"%s\",\"%s\"],[\"%s\",\"%s\"]],[\"%s\",\"%s\"]],\"%s\",\"0\",\"%s\"]\n", bal_s_str,cm_0_c0_x, cm_0_c0_y, cm_0_c1_x, cm_0_c1_y, sig_0_z_x, sig_0_z_y, sig_0_s_x, sig_0_s_y, sig_0_sh_x2, sig_0_sh_x1, sig_0_sh_y2, sig_0_sh_y1, sig_0_t_x, sig_0_t_y, amt_str, sig_str);

    // print_hex(sig_0_cpt, 65);
    char bal_t_str[257]={0};
    char c1_c0[1000], c1_c1[1000];
    char sig_1_z[1000], sig_1_s[1000], sig_1_sh[1000], sig_1_t[1000];
    mclBnFr_getStr(bal_t_str, 257, &bal_t, 10);
    mclBnG1_getStr(c1_c0, 1000, &(cm_1->c0), 10);
    mclBnG1_getStr(c1_c1, 1000, &(cm_1->c1), 10);

    mclBnG1_getStr(sig_1_z, 1000, &(sig_hat_1->z), 10);
    mclBnG1_getStr(sig_1_s, 1000, &(sig_hat_1->s), 10);
    mclBnG2_getStr(sig_1_sh, 1000, &(sig_hat_1->s_hat), 10);
    mclBnG1_getStr(sig_1_t, 1000, &(sig_hat_1->t), 10);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", bal_t_str,c1_c0,c1_c1,sig_1_z,sig_1_s,sig_1_sh,sig_1_t,r1_str);
    // printf("\nST1:\n");
    return 0;
}
