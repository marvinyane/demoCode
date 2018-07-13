#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/err.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



EVP_PKEY *my_pkey = NULL;

void getPubKeyFromFile(const char* keyfile)
{
    RSA *rsa_pub = PEM_read_RSA_PUBKEY(keyfile, NULL, NULL, NULL);
    return rsa_pub;
}


void getPubKeyFromCert(const char* cert_filestr)
{
    BIO* certbio = NULL;
    X509* my_cert = NULL;
    
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    certbio = BIO_new(BIO_s_file());

    BIO_read_filename(certbio, cert_filestr);

    my_cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);

    my_pkey = X509_get_pubkey(my_cert);

    printf("my pkey is %p\n", my_pkey);
}


int verify( char* msg_hash, int msg_hash_len, const char* msg, int msg_len)
{
    int result = -1;

    EVP_MD_CTX* ctx = EVP_MD_CTX_create();
    const EVP_MD* md = EVP_get_digestbyname( "SHA256" );
    EVP_DigestInit_ex( ctx, md, NULL );
    int ret = EVP_DigestVerifyInit( ctx, NULL, md, NULL, my_pkey );
    printf("init ret is %d\n", ret);

    ret =  EVP_DigestVerifyUpdate(ctx, msg, msg_len);
    printf("update ret is %d\n", ret);

    ret = EVP_DigestVerifyFinal(ctx, msg_hash, msg_hash_len);
    printf("final ret is %d\n", ret);

    EVP_MD_CTX_cleanup(ctx);
    return result;
}

int main(int argc, char** argv)
{
    int s_fp = open(argv[1], O_RDONLY);
    char sign[1024];
    memset(sign, 0, sizeof(sign));
    int sign_len  =  read(s_fp, sign, sizeof(sign));

    int v_len =  atoi(argv[3]);
    printf("verfied file len is %d\n", v_len);

    int v_fp = open(argv[2], O_RDONLY);

    char* v_buf = mmap(NULL, v_len, PROT_READ, MAP_PRIVATE, v_fp, 0);

    printf("mmap result %d\n", v_buf);


    /** int pkey_fd = fopen(argv[4], O_RDONLY); */
    /** int pkey_len = atoi(argv[5]); */
    /** printf("pkey len is %d \n", pkey_len); */
    /** char* pkey = malloc(pkey_len); */
    /** read(pkey_fd, pkey, pkey_len); */

    getPubKeyFromCert(argv[4]);

    verify(sign, sign_len, v_buf, v_len);
    return 0;
}

