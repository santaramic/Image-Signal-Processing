im=imread('doll.bmp');
[im1,map]=rgb2ind(im,4);
imwrite(im1,map,'dollindex.bmp');
[im2,map1]=imread('dollindex.bmp');
subplot(121)
imshow(im);
subplot(122)
imshow(im2,map1);
