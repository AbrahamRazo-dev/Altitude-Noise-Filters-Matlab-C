function data = MovAvgMain(v)
% MovAvgMain
% Aplica un moving average de ventana 3 a la senal de entrada.
%
% Entrada:
%   v : vector de entrada
%
% Salida:
%   data : vector filtrado con la misma longitud que v

    N = 3;
    data = MovAvg(v, N);
end
