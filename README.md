# GetClosestPointOnPolygon
The purpose of this function is to find the closest position to the cursor inside a room. You can assume that the polygon is not self intersecting.

struct Point {
    
    x: int;
    y: int;
}

function getClosestPointInsidePolygon(poly: Point[], pos: Point): Point {

// This function returns the closest point to the pos that is inside/on the polygon defined by "poly"

}

example input:

getClosestPointInsidePolygon([
     
      { x: 0, y: 0 },
      { x: 100, y: 0 },
      { x: 100, y: 100 },
      { x: 0, y: 100 }]

point { x: 150, y: 50 });

Output: { x: 100, y: 50 }. 

It also works with shapes more complex than a square.
