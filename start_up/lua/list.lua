#!/usr/bin/lua

polyline = { color = "blue", thickness = 2, npoints = 4, 
            { x = 11,  y = 0},
            { x = -10, y = 0},
            { x = 10,  y = 1},
        }

print(polyline.color);
print(polyline[2].x);
print(polyline[1].x);

