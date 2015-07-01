from mouse import moveTo
from generateData import generateData;
generateData();

from GaussNewtonMultiLat import getLocation, screen_Height
p = getLocation();
x = p[0];
y = p[1];
moveTo(x,screen_Height-y);
