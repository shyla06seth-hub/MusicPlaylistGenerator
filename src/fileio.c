#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

/* Save playlist to text file */
int save_playlist_to_file(Song *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file for saving.\n");
        return 0;
    }

    Song *cur = head;
    while (cur) {
        fprintf(fp, "%d|%s|%s|%s|%d\n",
                cur->id,
                cur->title,
                cur->artist,
                cur->album,
                cur->duration_sec);
        cur = cur->next;
    }

    fclose(fp);
    return 1;
}

/* Load playlist from file */
Song* load_playlist_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return NULL;   // file does not exist yet
    }

    Song *head = NULL;

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        Song *s = malloc(sizeof(Song));
        if (!s) break;

        sscanf(line, "%d|%99[^|]|%99[^|]|%99[^|]|%d",
               &s->id,
               s->title,
               s->artist,
               s->album,
               &s->duration_sec);

        s->next = NULL;
        s->prev = NULL;

        if (!head) {
            head = s;
        } else {
            Song *tail = head;
            while (tail->next) tail = tail->next;
            tail->next = s;
            s->prev = tail;
        }
    }

    fclose(fp);
    return head;
}

