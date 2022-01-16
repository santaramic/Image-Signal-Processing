%%
pw=16; % parameter to control the period(width)
f=imread('scene1.jpg');
 
fr=f(:,:,1);
[row ,col]=size(fr);
[y,x]=meshgrid(1:col,1:row);
y2=y+mod(y,pw); % subsampling effect
y2(find(y2<1))=1;
y2(find(y2>col))=col;
for i=1:row
 for j=1:col
 f2(i,j)=fr(x(i,j),y2(i,j));
 end
end
 
fg=f(:,:,2);
[row ,col]=size(fg);
[y,x]=meshgrid(1:col,1:row);
y3=y+mod(y,pw); % subsampling effect
y3(find(y3<1))=1;
y3(find(y3>col))=col;
for i=1:row
 for j=1:col
 f3(i,j)=fg(x(i,j),y3(i,j));
 end
end
 
fb=f(:,:,3);
[row ,col]=size(fb);
[y,x]=meshgrid(1:col,1:row);
y4=y+mod(y,pw); % subsampling effect
y4(find(y4<1))=1;
y4(find(y4>col))=col;
for i=1:row
 for j=1:col
 f4(i,j)=fb(x(i,j),y4(i,j));
 end
end
 
f5(:,:,1) = f2;
f5(:,:,2) = f3;
f5(:,:,3) = f4;
 
 
imshowpair(f,f5,'montage');
