function [RPm,RPc,RPa,ns,Ht,St,Gt,Cp] = tdclc(P0,T,C,W1,W2,M,RPm0,RPc0,RPa0,ns0)

if nargin < 7
    RPm0 = ones(1,size(W1,1));
    RPa0 = ones(1,length(C));
    RPc0 = ones(1,size(W2,1));
    ns0 = 1;
end

P0 = P0/101325; %Pa -> atm
i = @(num,T) 4.184*(M(num,2) + M(num,3)*(T*1e-3) + M(num,4)*(T*1e-3)^2+ M(num,5)*(T*1e-3)^3 + M(num,6)*(T*1e-3)^4 + M(num,7)*(T*1e-3)^5 + M(num,8)*(T*1e-3)^6 + M(num,9)*(T*1e-3)^7); %J/mole
s = @(num,T) 4.184*(M(num,1) + 1e-3*M(num,3)*log(T*1e-3) + 1e-3*(2*M(num,4)*(T*1e-3) + 3/2*M(num,5)*(T*1e-3)^2 + 4/3*M(num,6)*(T*1e-3)^3 + 5/4*M(num,7)*(T*1e-3)^4 + 6/5*M(num,8)*(T*1e-3)^5 + 7/6*M(num,9)*(T*1e-3)^6)); %J/mole
c = @(num,T) 4.184*1e-3*(1*M(num,3) + 2*M(num,4)*(T*1e-3) + 3*M(num,5)*(T*1e-3)^2 + 4*M(num,6)*(T*1e-3)^3 + 5*M(num,7)*(T*1e-3)^4 + 6*M(num,8)*(T*1e-3)^5 + 7*M(num,9)*(T*1e-3)^6); %J/mole

x0 = [RPm0 RPc0 RPa0]*ns0;
Aeq = [W1; W2; eye(length(C))]';
lb = zeros(1, size(Aeq,2));
ub = Inf*ones(1, size(Aeq,2));

opts = optimset('Algorithm', 'interior-point','Display','off');
%problem = createOptimProblem('fmincon','x0', x0, 'objective', @gibbs, 'lb', lb, 'ub', ub, 'Aeq', Aeq, 'beq', C, 'options', opts);
[X, Gt] = fmincon(@gibbs,x0,[],[],Aeq,C,lb,ub,[],opts);
ns = 0; Ht = 0; St = 0; Cp = 0;
for j = 1:length(X), 
    if (j <= size(W1,1))||(j > (size(W1,1)+size(W2,1))), ns = ns + X(j); end
    Ht = Ht + X(j)*i(j,T); % J/kg
    St = St + X(j)*s(j,T); % J/kg/K
end
for j = 1:length(X),
    if (j <= size(W1,1))||(j > (size(W1,1)+size(W2,1))), St = St - X(j)*8.314*log(X(j)/ns*P0); end
    if (j <= size(W1,1))||(j > (size(W1,1)+size(W2,1))), Cp = Cp + X(j)*c(j,T); end % J/kg/K
end

RPm = X(1:size(W1,1))/ns;
RPc = X((1+size(W1,1)):(size(W1,1)+size(W2,1)))/ns;
RPa = X((1+size(W1,1)+size(W2,1)):(size(W1,1)+size(W2,1)+length(C)))/ns;

%P = (sum(RPm) + sum(RPa))/P0;

    function G = gibbs(x)
        G = 0;
        xs = 0;
        for n = 1:length(x), 
            if (n <= size(W1,1))||(n > (size(W1,1)+size(W2,1))), xs = xs + x(n); end 
        end
        for n = 1:length(x) 
            G = G + x(n)*(i(n,T)-T*s(n,T));
            if (n <= size(W1,1))||(n > (size(W1,1)+size(W2,1))), G = G + x(n)*8.314*T*log(x(n)/xs*P0); end 
        end
    end


end

