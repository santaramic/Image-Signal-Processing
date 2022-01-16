I =im2double(rgb2gray(imread('doll.bmp')));
BW = edge(I,'canny');
BW2 = edge(I,'canny',[0.2 0.3], 1.5);
 
imshowpair(BW,BW2,'montage')
