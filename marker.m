% mark the place that sum of RGB value is the highest

clear all;
close all;
P = im2double(imread('test1.jpg'));
imshow(P);
[MP NP CP] = size(P);
sum_RGB = P(:,:,1)+P(:,:,2)+P(:,:,3);
max_RGB = max(sum_RGB,[],'all')
[max_row,max_col] = find(sum_RGB==max_RGB,1)
marker = insertMarker(P, [max_col,max_row] , 'color', 'red', 'Size', 8);
imshow(marker)
