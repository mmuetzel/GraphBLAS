
A = zeros (4,4) ;

for i = 0:3
    for j = 0:3
        A(i+1,j+1) = (i+1) + 1i * (2-j) ;
    end
end

A
sum(A, 'all')

A = A^2
sum (A, 'all')

