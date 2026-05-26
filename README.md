# assignments

use the main.c code as a starting point. You can write a function and add it to the update function to see the results.

The code is untested, it's mostly a general outline rather than a ready to use template.

## Tasks

- create simple shapes (triangles, squares, circles, hexagons, etc)
- work in NDC space and translate to screen space
```
typedef struct {
	int x;
	int y;
} Vec;

void ndc_to_sc(Vec *v, int width, int height) {
}

void generate_image(int width, int height) {
	Vec triangle[] = {
		(Vec) {.x = 0, .y = 0.5},
		(Vec) {.x = 0.5, y = -0.5},
		(Vec) {.x = -.5, y = -0.5},
	};

	Vec triangles_new[3] = {0};
	for (int i = 0;i < sizeof(triangles)/sizeof(Vec);++i) {
		Vec v = triangles[i];
		ndc_to_sc(&v, width, height);
		triangles_new[i] = v;
		
		if (i == 0)
			continue;
		draw_line(triangles[i-1], triangles[i]);
	}
}
```
- write a scaling animation (based on time)
