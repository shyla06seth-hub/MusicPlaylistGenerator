#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

/* Create a new Song struct and return pointer. id set later by add_song_end */
Song* create_song(const char* title, const char* artist, const char* album, int duration) {
    Song *s = (Song*)malloc(sizeof(Song));
    if (!s) return NULL;

    s->id = -1;
    /* use strncpy to avoid overflow and ensure null-termination */
    strncpy(s->title, title ? title : "", sizeof s->title - 1);
    s->title[sizeof s->title - 1] = '\0';
    strncpy(s->artist, artist ? artist : "", sizeof s->artist - 1);
    s->artist[sizeof s->artist - 1] = '\0';
    strncpy(s->album, album ? album : "", sizeof s->album - 1);
    s->album[sizeof s->album - 1] = '\0';

    s->duration_sec = duration;
    s->next = NULL;
    s->prev = NULL;
    return s;
}

/* Return next id = max existing id + 1 (start from 1) */
int get_next_id(Song *head) {
    if (!head) return 1;
    int max = 0;
    Song *cur = head;
    while (cur) {
        if (cur->id > max) max = cur->id;
        cur = cur->next;
    }
    return max + 1;
}

/* Append song to end of doubly-linked list and assign id */
void add_song_end(Song **head, Song *new_song) {
    if (!new_song) return;
    new_song->next = new_song->prev = NULL;

    if (!(*head)) {
        new_song->id = get_next_id(NULL); /* returns 1 */
        *head = new_song;
        return;
    }

    Song *tail = *head;
    while (tail->next) tail = tail->next;

    new_song->id = get_next_id(*head);
    tail->next = new_song;
    new_song->prev = tail;
}

/* Print one song in readable, column-aligned format */
void display_song(Song *s) {
    if (!s) return;
    int mm = s->duration_sec / 60;
    int ss = s->duration_sec % 60;
    printf("%-4d %-15s %-15s %-15s %2d:%02d\n",
           s->id,
           s->title,
           s->artist,
           s->album,
           mm, ss);
}

/* Display all songs in a neat table */
void display_all_songs(Song *head) {
    if (!head) {
        printf("Playlist is empty.\n");
        return;
    }

    printf("\n%-4s %-15s %-15s %-15s %s\n",
           "ID", "TITLE", "ARTIST", "ALBUM", "DURATION");
    printf("---------------------------------------------------------------\n");

    Song *cur = head;
    while (cur) {
        display_song(cur);
        cur = cur->next;
    }
}

/* Free all nodes (used on exit) */
void free_playlist(Song **head) {
    if (!head || !*head) return;
    Song *cur = *head;
    while (cur) {
        Song *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}

/* Delete a song by its ID. Returns 1 on success, 0 if ID not found. */
int delete_song_by_id(Song **head, int id) {
    if (!head || !*head) return 0;

    Song *cur = *head;

    /* search for song with matching ID */
    while (cur && cur->id != id) {
        cur = cur->next;
    }

    if (!cur) return 0;  /* ID not found */

    /* deleting head */
    if (cur == *head) {
        *head = cur->next;
        if (*head) (*head)->prev = NULL;
    } else {
        /* deleting middle or last node */
        cur->prev->next = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
    }

    free(cur);
    return 1;  /* success */
}

/* Search song by exact title (case-sensitive). Returns pointer or NULL. */
Song* search_song_by_title(Song *head, const char *title) {
    if (!head || !title) return NULL;
    Song *cur = head;
    while (cur) {
        if (strcmp(cur->title, title) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void sort_playlist_by_title(Song **head) {
    if (!head || !*head || !(*head)->next)
        return;  // empty or single song

    Song *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->title, j->title) > 0) {
                // swap song data (not nodes)
                Song temp = *i;
                Song *iprev = i->prev;
                Song *inext = i->next;
                Song *jprev = j->prev;
                Song *jnext = j->next;

                *i = *j;
                *j = temp;

                i->prev = iprev;
                i->next = inext;
                j->prev = jprev;
                j->next = jnext;
            }
        }
    }
}
