#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>


int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "TickTock");
    while (!WindowShouldClose()) {
        int width = GetScreenWidth();
        int height = GetScreenHeight();
        Vector2 mid = {
            width / 2.,
            height / 2.
        };
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        struct timeval now;
        gettimeofday(&now, NULL);
        float radius = (width > height ? height : width) * .75 * .5;
        BeginDrawing();

            // DrawRing(
            //         mid,
            //         radius,
            //         radius + 2,
            //         0,
            //         360,
            //         100,
            //         LIGHTGRAY
            //         );

            for (int i = 60; i-- > 0;) {
                float angle = i / 60. * PI * 2 - PI / 2.;

                Vector2 vec = {
                    .x = cos(angle),
                    .y = sin(angle)
                };

                if (i % 5) {
                    Vector2 start = Vector2Add(Vector2Scale(vec, radius), mid);
                    Vector2 end = Vector2Add(Vector2Scale(vec, radius + 10), mid);

                    DrawLineEx(start, end, 2, LIGHTGRAY);
                } else {
                    Vector2 start = Vector2Add(Vector2Scale(vec, radius - 10), mid);
                    Vector2 end = Vector2Add(Vector2Scale(vec, radius + 10), mid);

                    DrawLineEx(start, end, 3, LIGHTGRAY);
                }
            }

            {
                float angle = (timeinfo->tm_sec + now.tv_usec / (1000. * 1000.)) / 60. * PI * 2 - (PI / 2.);

                float x = cos(angle) * radius;
                float y = sin(angle) * radius;

                DrawLineEx(mid, Vector2Add((Vector2) { x, y }, mid), 2, RED);
            }

            {
                float angle = (timeinfo->tm_min + timeinfo->tm_sec / 60.) / 60. * PI * 2 - (PI / 2.);

                float x = cos(angle) * (radius - 10);
                float y = sin(angle) * (radius - 10);

                DrawLineEx(mid, Vector2Add((Vector2) { x, y }, mid), 5, RAYWHITE);
            }

            {
                float angle = (timeinfo->tm_hour + timeinfo->tm_min / 60.) / 12. * PI * 2 - (PI / 2.);

                float x = cos(angle) * radius * .75;
                float y = sin(angle) * radius * .75;

                DrawLineEx(mid, Vector2Add((Vector2) { x, y }, mid), 8, LIGHTGRAY);
            }

            DrawCircleV(mid, 8, GRAY);

            ClearBackground(BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
