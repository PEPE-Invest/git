#ifndef COMMIT_GRAPH_H
#define COMMIT_GRAPH_H

#include "git-compat-util.h"

extern char *get_graph_latest_filename(const char *obj_dir);
extern char *get_graph_latest_contents(const char *obj_dir);

/*
 * Given a commit struct, try to fill the commit struct info, including:
 *  1. tree object
 *  2. date
 *  3. parents.
 *
 * Returns 1 if and only if the commit was found in the packed graph.
 *
 * See parse_commit_buffer() for the fallback after this call.
 */
extern int parse_commit_in_graph(struct commit *item);

extern struct commit_graph {
	int graph_fd;

	const unsigned char *data;
	size_t data_len;

	unsigned char hash_len;
	unsigned char num_chunks;
	uint32_t num_commits;
	struct object_id oid;

	const uint32_t *chunk_oid_fanout;
	const unsigned char *chunk_oid_lookup;
	const unsigned char *chunk_commit_data;
	const unsigned char *chunk_large_edges;
} *commit_graph;

extern struct commit_graph *load_commit_graph_one(const char *graph_file);

extern void prepare_commit_graph(void);

extern char *write_commit_graph(const char *obj_dir);

#endif
