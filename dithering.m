clc, clear
im_doll =rgb2gray(imread('doll.bmp'));
[m n]=size(im_doll); 
 
% 4x4 Dither matrix
D2=[0 128 32 160;192 64 224 96;48 176 16 144;240 112 208 80];
[d2m d2n]=size(D2);
R2=repmat(D2,fix(m/d2m)+1,fix(n/d2n)+1);
[R2m R2n]=size(R2);
if m~=R2m || n~=R2n
    R2=R2(1:m,1:n);
end
im_doll_D2=im_doll>R2;
 
% 3x3 Dither matrix
D3=[224 112 196; 28 0 84; 140 56 168];
[d3m d3n]=size(D3);
R3=repmat(D3,fix(m/d3m)+1,fix(n/d3n)+1);
[R3m R3n]=size(R3);
if m~=R3m || n~=R3n
    R3=R3(1:m,1:n);
end
im_doll_D3=im_doll>R3;
 
figure;
imshowpair(im_doll_D2,im_doll_D3,'montage')
