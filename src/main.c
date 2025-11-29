#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"
#include "fileio.h"
#include "utils.h"

int main(void) {
    Song *playlist = NULL;

    /* Try load from file (function currently returns NULL - that's fine) */
    playlist = load_playlist_from_file("playlist.txt");

    while (1) {
        printf("\n=== Music Playlist Generator ===\n");
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Search song\n");
        printf("4. Display all songs\n");
        printf("5. Save & Exit\n");
        printf("6. Sort playlist by title\n");
        printf("Choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input. Try again.\n");
            continue;
        }
        clear_input_buffer();

        if (choice == 1) {
            char title[100], artist[100], album[100];
            int duration;

            printf("Enter Title: ");
            if (!fgets(title, sizeof title, stdin)) { clear_input_buffer(); continue; }
            trim_newline(title);

            printf("Enter Artist: ");
            if (!fgets(artist, sizeof artist, stdin)) { clear_input_buffer(); continue; }
            trim_newline(artist);

            printf("Enter Album: ");
            if (!fgets(album, sizeof album, stdin)) { clear_input_buffer(); continue; }
            trim_newline(album);

            printf("Enter Duration (seconds): ");
            if (scanf("%d", &duration) != 1) { clear_input_buffer(); printf("Invalid duration.\n"); continue; }
            clear_input_buffer();

            Song *s = create_song(title, artist, album, duration);
            if (!s) {
                printf("Memory error: could not create song.\n");
                continue;
            }
            add_song_end(&playlist, s);
            printf("Song added with ID %d\n", s->id);
        } else if (choice == 2) {
            int id;
            printf("Enter Song ID to delete: ");
            if (scanf("%d", &id) != 1) {
                clear_input_buffer();
                printf("Invalid input.\n");
                continue;
            }
            clear_input_buffer();

            if (delete_song_by_id(&playlist, id)) {
                printf("Song deleted successfully.\n");
            } else {
                printf("Song with ID %d not found.\n", id);
            }
        } else if (choice == 3) {
    char title[100];

    printf("Enter song title to search: ");
    if (!fgets(title, sizeof title, stdin)) {
        clear_input_buffer();
        continue;
    }
    trim_newline(title);

            Song *found = search_song_by_title(playlist, title);
            if (found) {
                display_song(found);
            } else {
                printf("Song not found.\n");
            }
        } else if (choice == 4) {
            display_all_songs(playlist);
            } else if (choice == 6) {
    sort_playlist_by_title(&playlist);
    printf("Playlist sorted by title.\n");

        } else if (choice == 5) {
            /* Save to file (currently placeholder) */
            save_playlist_to_file(playlist, "playlist.txt");
            free_playlist(&playlist);
            printf("Saved and exiting. Bye!\n");
            break;
        } else {
            printf("Invalid choice. Enter number 1-5.\n");
        }
    }

    return 0;
}

