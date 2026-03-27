%% prueba_filtro_csv.m
% Prueba del filtro con datos cargados desde CSV
%
% Este script:
% 1) Carga los vectores x e y desde datos_x.csv y datos_y.csv
% 2) Ejecuta MovAvgMain.m, que usa MovingAverage.m
% 3) Grafica la senal original y la senal filtrada
% 4) Calcula la misma metrica de eficiencia que tu ejemplo:
%
%    eficiencia_prr = (1 - var(y_filtrada) / var(y_original)) * 100
%
% ignorando el primer 10% por transitorio.

clear; clc; close all;

%% Verificacion de archivos
if ~isfile('datos_x.csv')
    error('No se encontro el archivo datos_x.csv en la carpeta actual.');
end

if ~isfile('datos_y.csv')
    error('No se encontro el archivo datos_y.csv en la carpeta actual.');
end

if ~isfile('MovAvgMain.m')
    error('No se encontro el archivo MovAvgMain.m en la carpeta actual.');
end

if ~isfile('MovAvg.m')
    error('No se encontro el archivo MovingAverage.m en la carpeta actual.');
end

%% Carga de datos
x_tbl = readtable('datos_x.csv');
y_tbl = readtable('datos_y.csv');

datax = x_tbl{:,1};
datay = y_tbl{:,1};

datax = datax(:);
datay = datay(:);

if isempty(datax) || isempty(datay)
    error('Alguno de los vectores esta vacio.');
end

if length(datax) ~= length(datay)
    error('Los vectores x e y no tienen la misma longitud. x=%d, y=%d', length(datax), length(datay));
end

%% Aplicacion del filtro
y_filtered = MovAvgMain(datay);
y_filtered = y_filtered(:);

if isempty(y_filtered)
    error('La salida de MovAvgMain esta vacia.');
end

if length(y_filtered) ~= length(datay)
    error('La senal filtrada y la original no tienen la misma longitud.');
end

%% Grafica principal
figure('Name', 'System Response vs Filtered', 'Color', 'w');

plot(datax, datay, 'LineWidth', 2)
hold on
plot(datax, y_filtered, 'LineWidth', 2)

grid on
box on

xlabel('Time (s)', 'FontSize', 12)
ylabel('Response', 'FontSize', 12)
title('System Response vs Filtered', 'FontSize', 14)

legend({'Measured', 'Filtered'}, 'Location', 'best')
set(gca, 'FontSize', 12)

%% Metrica EXACTAMENTE como tu ejemplo
% 1. Definir el punto de inicio (ignorar el primer 10% por el transitorio)
n = length(datay);
recorte = round(n * 0.1);

if recorte == 0
    recorte = 1;
end

% 2. Crear el indice de comparacion (del recorte al final)
idx = recorte:n;

% 3. Calcular varianzas solo en ese rango
var_ruidosa  = var(datay(idx));
var_filtrada = var(y_filtered(idx));

% 4. Metrica de Eficiencia: Porcentaje de Ruido Eliminado (PRE)
eficiencia_prr = (1 - (var_filtrada / var_ruidosa)) * 100;

% 5. Mostrar resultado rapido
fprintf('--- Resultado de Eficiencia ---\n');
fprintf('Ruido eliminado: %.2f%%\n', eficiencia_prr);

%% Visualizacion del "Termometro"
figure('Name', 'Eficiencia del Filtro', 'Color', 'w');
bar(eficiencia_prr, 'FaceColor', [0.2 0.6 0.5]);
ylabel('Porcentaje (%)');
ylim([-20 100]);
grid on;
title(['Eficiencia Concreta: ', num2str(eficiencia_prr, '%.2f'), '%']);
set(gca, 'XTick', 1);
set(gca, 'XTickLabel', {'Reduccion de Ruido'});