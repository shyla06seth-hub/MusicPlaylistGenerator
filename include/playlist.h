#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Song {
    int id;
    char title[100];
    char artist[100];
    char album[100];
    int duration_sec;
    struct Song *next;
    struct Song *prev;
} Song;

Song* create_song(const char* title, const char* artist, const char* album, int duration);
void add_song_end(Song **head, Song *new_song);
int delete_song_by_id(Song **head, int id);
Song* search_song_by_title(Song *head, const char *title);
void display_all_songs(Song *head);
void free_playlist(Song **head);
int get_next_id(Song *head);
void display_song(Song *s);
void sort_playlist_by_title(Song **head);


#endif
