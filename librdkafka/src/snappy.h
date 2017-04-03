#ifndef _LINUX_SNAPPY_H
#define _LINUX_SNAPPY_H 1

#if !defined(__cplusplus) && defined(_WIN32) && _MSC_VER < 1800
typedef int bool
#define true 1
#define false 0
#else
#include <stdbool.h>
#endif
#include <stddef.h>

/* Only needed for compression. This preallocates the worst case */
struct snappy_env {
	unsigned short *hash_table;
	void *scratch;
	void *scratch_output;
};

struct iovec;
int rd_kafka_snappy_init_env(struct snappy_env *env);
int rd_kafka_snappy_init_env_sg(struct snappy_env *env, bool sg);
void rd_kafka_snappy_free_env(struct snappy_env *env);
int rd_kafka_snappy_uncompress_iov(struct iovec *iov_in, int iov_in_len,
			   size_t input_len, char *uncompressed);
int rd_kafka_snappy_uncompress(const char *compressed, size_t n, char *uncompressed);
int rd_kafka_snappy_compress(struct snappy_env *env,
		    const char *input,
		    size_t input_length,
		    char *compressed,
		    size_t *compressed_length);
int rd_kafka_snappy_compress_iov(struct snappy_env *env,
			struct iovec *iov_in,
			int iov_in_len,
			size_t input_length,
			struct iovec *iov_out,
			int *iov_out_len,
			size_t *compressed_length);
bool rd_kafka_snappy_uncompressed_length(const char *buf, size_t len, size_t *result);
size_t rd_kafka_snappy_max_compressed_length(size_t source_len);




#endif
