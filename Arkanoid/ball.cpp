#define _USE_MATH_DEFINES

#include <ctime>
#include <cmath>
#include "ball.h"

Ball::Ball(int x, int y) :Actor(BallSprite, x, y, BallDiameter, BallDiameter)
{
}

bool Ball::bounce()
{
    int diameter = 0, diameter2 = 0, width = 0, height = 0;

    if (xpos <= 0)
    {
        xspeed *= -1;
        xpos = 0;
    }
    else if (xpos + BallDiameter >= Width)
    {
        xspeed *= -1;
        xpos = Width - BallDiameter;
    }
    if (ypos <= 0)
    {
        yspeed *= -1;
    }

    bounceFromBricks();

    if (barrierUp)
    {
        bounceFromBarrier();
    }
    
    return bounceFromPlatform();
}

void Ball::bounceFromBricks()
{
    //Center of the ball
    coordinates cball;
    int r = BallDiameter / 2;
    cball.x = xpos + r;
    cball.y = ypos + r;

    bool xcollision = false;
    bool ycollision = false;

    vector<coordinates>::iterator i;
    for (i = bricksList.begin(); i != bricksList.end(); ++i)
    {
        //break the brick down into four line segments and check if they intersect
        coordinates LUcorner, LDcorner, RUcorner, RDcorner;
        LUcorner = *i;
        LDcorner.x = i->x; LDcorner.y = i->y + BrickHeight;
        RUcorner.x = i->x + BrickWidth; RUcorner.y = i->y;
        RDcorner.x = i->x + BrickWidth; RDcorner.y = i->y + BrickHeight;

        char linesIntersected = 0;
        if (ballLineIntersection(cball, r, LUcorner, LDcorner) || ballLineIntersection(cball, r, RUcorner, RDcorner) ||
            ballLineIntersection(cball, r, LUcorner, RUcorner) || ballLineIntersection(cball, r, LDcorner, RDcorner))
        {
            if (cball.x>LUcorner.x && cball.x < RUcorner.x)// collided with horisontal line
            {
                xcollision = true;
                yspeed *= -1;
            }
            else if (cball.y > LUcorner.y && cball.y < LDcorner.y)//colided with vertical line
            {
                ycollision = true;
                xspeed *= -1;
            }
            else if(!xcollision && !ycollision)//hit the corner.
            {
                xcollision = true; ycollision = true;

                //if the ball did hit a corner, then it will reflect from imaginary line,
                //perpendicular to the line from ball`s center to the corner.
                //at least it should

                //first find THE corner, the ball colided with
                coordinates TheCorner;
                if (cball.x<LUcorner.x && cball.y < LUcorner.y)
                {
                    TheCorner = LUcorner;
                }
                else if (cball.x > RUcorner.x && cball.y < RUcorner.y)
                {
                    TheCorner = RUcorner;
                }
                else if (cball.x < LDcorner.x && cball.y > LDcorner.y)
                {
                    TheCorner = LDcorner;
                }
                else
                {
                    TheCorner = RUcorner;
                }

                //find the normal vector
                coordinates nvector;
                nvector.x = cball.x - TheCorner.x;
                nvector.y = cball.y - TheCorner.y;

                //project speed vector on normal vector
                float scalar = (xspeed * nvector.x + yspeed * nvector.y) / (nvector.x * nvector.x + nvector.y * nvector.y);
                coordinates projection;
                projection.x = nvector.x * scalar;
                projection.y = nvector.y * scalar;

                //reflect
                xspeed -= 2 * projection.x;
                yspeed -= 2 * projection.y;
            }
            
            i->x = -1;
            i->y = -1;

            if (xcollision && ycollision)
                return;
        }
    }
}

bool Ball::bounceFromPlatform()
{
    //Center of the ball
    coordinates cball;
    int r = BallDiameter / 2;
    cball.x = xpos + r;
    cball.y = ypos + r;
    
    //For now only the upper edge of the platform matters
    coordinates Lcorner, Rcorner;
    Lcorner.x = platformPosition; Lcorner.y = Height - PlatformHeight;
    Rcorner.x = Lcorner.x + PlatformWidth; Rcorner.y = Lcorner.y;
    if (ballLineIntersection(cball, r, Lcorner, Rcorner))
    {
        //When ball collides with the platform, it is launched in the dirrection, 
        //opposite to middle down point of the platform
        int MDx = platformPosition + PlatformWidth / 2;
        int MDy = Height;
        launch(2 * cball.x - MDx, 2 * cball.y - MDy);

        return true;
    }
    return false;
}

void Ball::bounceFromBarrier()
{
    if (ypos>=Height-(PlatformHeight/2)-BallDiameter)
    {
        yspeed *= -1;
        barrierUp = false;
    }
}

bool Ball::isOut()
{
    return ypos > Height;
}

bool Ball::tick()
{
    __super::tick();
    return bounce();
}

void Ball::launch(int xdir, int ydir)
{
    int diameter = 0, diameter2 = 0;
    getSpriteSize(sprite, diameter, diameter2);
    float xcenter = xpos + (diameter / 2);
    float ycenter = ypos + (diameter / 2);
    float xdistance = xdir - xcenter;
    float ydistance = ydir - ycenter;
    float distance = sqrtf(xdistance * xdistance + ydistance * ydistance);
    float ratio = speed / distance;
    xspeed = xdistance * ratio;
    yspeed = ydistance * ratio;
}