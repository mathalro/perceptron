function [a] = hardlim(n)
	for i = 1:size(n,1)
		for j = 1:size(n,2)
			if n(i,j) >= 0
				n(i,j) = 1;
			else
				n(i,j) = 0;
			end
		end
	end
	a = n;
end