/*
 * Copyright (c) 2005 - 2006 Kungliga Tekniska H�gskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* $Id$ */

#ifndef HEIM_EVP_H
#define HEIM_EVP_H 1

#include <hcrypto/engine.h>

/* symbol renaming */
#define EVP_CIPHER_CTX_block_size hc_EVP_CIPHER_CTX_block_size
#define EVP_CIPHER_CTX_cipher hc_EVP_CIPHER_CTX_cipher
#define EVP_CIPHER_CTX_cleanup hc_EVP_CIPHER_CTX_cleanup
#define EVP_CIPHER_CTX_flags hc_EVP_CIPHER_CTX_flags
#define EVP_CIPHER_CTX_get_app_data hc_EVP_CIPHER_CTX_get_app_data
#define EVP_CIPHER_CTX_init hc_EVP_CIPHER_CTX_init
#define EVP_CIPHER_CTX_iv_length hc_EVP_CIPHER_CTX_iv_length
#define EVP_CIPHER_CTX_key_length hc_EVP_CIPHER_CTX_key_length
#define EVP_CIPHER_CTX_mode hc_EVP_CIPHER_CTX_mode
#define EVP_CIPHER_CTX_set_app_data hc_EVP_CIPHER_CTX_set_app_data
#define EVP_CIPHER_CTX_set_key_length hc_EVP_CIPHER_CTX_set_key_length
#define EVP_CIPHER_CTX_set_padding hc_EVP_CIPHER_CTX_set_padding
#define EVP_CIPHER_block_size hc_EVP_CIPHER_block_size
#define EVP_CIPHER_iv_length hc_EVP_CIPHER_iv_length
#define EVP_CIPHER_key_length hc_EVP_CIPHER_key_length
#define EVP_Cipher hc_EVP_Cipher
#define EVP_CipherInit_ex hc_EVP_CipherInit_ex
#define EVP_Digest hc_EVP_Digest
#define EVP_DigestFinal_ex hc_EVP_DigestFinal_ex
#define EVP_DigestInit_ex hc_EVP_DigestInit_ex
#define EVP_DigestUpdate hc_EVP_DigestUpdate
#define EVP_MD_CTX_block_size hc_EVP_MD_CTX_block_size
#define EVP_MD_CTX_cleanup hc_EVP_MD_CTX_cleanup
#define EVP_MD_CTX_create hc_EVP_MD_CTX_create
#define EVP_MD_CTX_init hc_EVP_MD_CTX_init
#define EVP_MD_CTX_destroy hc_EVP_MD_CTX_destroy
#define EVP_MD_CTX_md hc_EVP_MD_CTX_md
#define EVP_MD_CTX_size hc_EVP_MD_CTX_size
#define EVP_MD_block_size hc_EVP_MD_block_size
#define EVP_MD_size hc_EVP_MD_size
#define EVP_aes_128_cbc hc_EVP_aes_128_cbc
#define EVP_aes_192_cbc hc_EVP_aes_192_cbc
#define EVP_aes_256_cbc hc_EVP_aes_256_cbc
#define EVP_des_ede3_cbc hc_EVP_des_ede3_cbc
#define EVP_enc_null hc_EVP_enc_null
#define EVP_md2 hc_EVP_md2
#define EVP_md4 hc_EVP_md4
#define EVP_md5 hc_EVP_md5
#define EVP_md_null hc_EVP_md_null
#define EVP_rc2_40_cbc hc_EVP_rc2_40_cbc
#define EVP_rc2_64_cbc hc_EVP_rc2_64_cbc
#define EVP_rc2_cbc hc_EVP_rc2_cbc
#define EVP_rc4 hc_EVP_rc4
#define EVP_rc4_40 hc_EVP_rc4_40
#define EVP_sha hc_EVP_sha
#define EVP_sha1 hc_EVP_sha1
#define EVP_sha256 hc_EVP_sha256
#define PKCS5_PBKDF2_HMAC_SHA1 hc_PKCS5_PBKDF2_HMAC_SHA1

/*
 *
 */

typedef struct hc_EVP_MD_CTX EVP_MD_CTX;
typedef struct hc_evp_pkey EVP_PKEY;
typedef struct hc_evp_md EVP_MD;
typedef struct hc_CIPHER EVP_CIPHER;
typedef struct hc_CIPHER_CTX EVP_CIPHER_CTX;

#define EVP_MAX_IV_LENGTH	16
#define EVP_MAX_BLOCK_LENGTH	32

#define EVP_MAX_MD_SIZE		64

struct hc_CIPHER {
    int nid;
    int block_size;
    int key_len;
    int iv_len;
    unsigned long flags;
    /* The lowest 3 bits is used as integer field for the mode the
     * cipher is used in (use EVP_CIPHER.._mode() to extract the
     * mode). The rest of the flag field is a bitfield.
     */
#define EVP_CIPH_CBC_MODE		2
#define EVP_CIPH_MODE			0x7

#define EVP_CIPH_ALWAYS_CALL_INIT	0x20

    int (*init)(EVP_CIPHER_CTX*,const unsigned char*,const unsigned char*,int);
    int (*do_cipher)(EVP_CIPHER_CTX *, unsigned char *,
		     const unsigned char *, unsigned int);
    int (*cleanup)(EVP_CIPHER_CTX *);
    int ctx_size;
    void *set_asn1_parameters;
    void *get_asn1_parameters;
    void *ctrl;
    void *app_data;
};

struct hc_CIPHER_CTX {
    const EVP_CIPHER *cipher;
    ENGINE *engine;
    int encrypt;
    int buf_len;
    unsigned char oiv[EVP_MAX_IV_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char buf[EVP_MAX_BLOCK_LENGTH];
    int num;
    void *app_data;
    int key_len;
    unsigned long flags;
    void *cipher_data;
    int final_used;
    int block_mask;
    unsigned char final[EVP_MAX_BLOCK_LENGTH];
};

struct hc_EVP_MD_CTX {
    const EVP_MD *md;
    ENGINE *engine;
    void *ptr;
};

/*
 * Avaible crypto algs
 */

const EVP_MD *EVP_md_null(void);
const EVP_MD *EVP_md2(void);
const EVP_MD *EVP_md4(void);
const EVP_MD *EVP_md5(void);
const EVP_MD *EVP_sha(void);
const EVP_MD *EVP_sha1(void);
const EVP_MD *EVP_sha256(void);

const EVP_CIPHER * EVP_aes_128_cbc(void);
const EVP_CIPHER * EVP_aes_192_cbc(void);
const EVP_CIPHER * EVP_aes_256_cbc(void);
const EVP_CIPHER * EVP_des_ede3_cbc(void);
const EVP_CIPHER * EVP_enc_null(void);
const EVP_CIPHER * EVP_rc2_40_cbc(void);
const EVP_CIPHER * EVP_rc2_64_cbc(void);
const EVP_CIPHER * EVP_rc2_cbc(void);
const EVP_CIPHER * EVP_rc4(void);
const EVP_CIPHER * EVP_rc4_40(void);

/*
 *
 */

size_t	EVP_MD_size(const EVP_MD *);
size_t	EVP_MD_block_size(const EVP_MD *);

const EVP_MD *
	EVP_MD_CTX_md(EVP_MD_CTX *);
size_t	EVP_MD_CTX_size(EVP_MD_CTX *);
size_t	EVP_MD_CTX_block_size(EVP_MD_CTX *);

EVP_MD_CTX *
	EVP_MD_CTX_create(void);
void	EVP_MD_CTX_init(EVP_MD_CTX *);
void	EVP_MD_CTX_destroy(EVP_MD_CTX *);
int	EVP_MD_CTX_cleanup(EVP_MD_CTX *);

int	EVP_DigestInit_ex(EVP_MD_CTX *, const EVP_MD *, ENGINE *);
int	EVP_DigestUpdate(EVP_MD_CTX *,const void *, size_t);
int	EVP_DigestFinal_ex(EVP_MD_CTX *, void *, unsigned int *);
int	EVP_Digest(const void *, size_t, void *, unsigned int *, 
		   const EVP_MD *, ENGINE *);
/*
 *
 */

size_t	EVP_CIPHER_block_size(const EVP_CIPHER *);
size_t	EVP_CIPHER_key_length(const EVP_CIPHER *);
size_t	EVP_CIPHER_iv_length(const EVP_CIPHER *);

void	EVP_CIPHER_CTX_init(EVP_CIPHER_CTX *);
int	EVP_CIPHER_CTX_cleanup(EVP_CIPHER_CTX *);
int	EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX *, int);
int	EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *, int);
unsigned long
	EVP_CIPHER_CTX_flags(const EVP_CIPHER_CTX *);
int	EVP_CIPHER_CTX_mode(const EVP_CIPHER_CTX *);

const EVP_CIPHER *
	EVP_CIPHER_CTX_cipher(EVP_CIPHER_CTX *);
size_t	EVP_CIPHER_CTX_block_size(const EVP_CIPHER_CTX *);
size_t	EVP_CIPHER_CTX_key_length(const EVP_CIPHER_CTX *);
size_t	EVP_CIPHER_CTX_iv_length(const EVP_CIPHER_CTX *);
void *	EVP_CIPHER_CTX_get_app_data(EVP_CIPHER_CTX *);
void	EVP_CIPHER_CTX_set_app_data(EVP_CIPHER_CTX *, void *);

int	EVP_CipherInit_ex(EVP_CIPHER_CTX *,const EVP_CIPHER *, ENGINE *,
			  const void *, const void *, int);

int	EVP_Cipher(EVP_CIPHER_CTX *,void *,const void *,size_t);

int	PKCS5_PBKDF2_HMAC_SHA1(const void *, size_t, const void *, size_t,
			       unsigned long, size_t, void *);


#endif /* HEIM_EVP_H */
