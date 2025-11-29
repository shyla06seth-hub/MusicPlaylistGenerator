#ifndef FILEIO_H
#define FILEIO_H

#include "playlist.h"

int save_playlist_to_file(Song *head, const char *filename);
Song* load_playlist_from_file(const char *filename);

#endif
