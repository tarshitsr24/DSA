class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {
        
        // Find the closest x-coordinate in the rectangle
        int closestX = max(x1, min(xCenter, x2));
        
        // Find the closest y-coordinate in the rectangle
        int closestY = max(y1, min(yCenter, y2));
        
        // Distance squared between circle center and closest point
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;
        
        return dx * dx + dy * dy <= radius * radius;
    }
};