M = csvread('data.csv');
M_binary_classes = zeros(size(M,1),3);
total = zeros(size(M,1)+3,size(M,2)-1);
for i = 1:size(M,1)
    if(M(i,1) == 1)
        M_binary_classes(i,1) = 1;
        M_binary_classes(i,2) = 0;
        M_binary_classes(i,3) = 0;
    end
    if(M(i,1) == 2)
        M_binary_classes(i,1) = 0;
        M_binary_classes(i,2) = 1;
        M_binary_classes(i,3) = 0;
    end
    if(M(i,1) == 3)
        M_binary_classes(i,1) = 0;
        M_binary_classes(i,2) = 0;
        M_binary_classes(i,3) = 1;
    end
    total = [M_binary_classes M(:,2:14)];
end

bias = ones(size(total,1),1);
D = total(:,1:3);
aux = total(:,4:16);
X = [bias aux];

W = zeros(size(D,2),size(X,2));
t = 1;
E = 1;
max_it = 10;
N = size(X,1);
X_transp = X';
alpha = 0.1;
E_epoca = [];
while t < max_it && E > 0
   E = 0;
   for i = 1:N
       yi = hardlim(W*X_transp(:,i));
       ei = D(i,:)' - yi;
       W = W + alpha*ei*X(i,:);
       E = E + ei*ei';
   end
   t = t+1;
   E_epoca = [E_epoca E];
end