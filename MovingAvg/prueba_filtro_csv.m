%% prueba_filtro_csv.m
% Prueba del filtro con datos cargados desde CSV
% Este script:
% 1) Carga los vectores x e y desde datos_x.csv y datos_y.csv
% 2) Ejecuta el script/funcion main.m, que a su vez usa Filtro.m
% 3) Grafica la señal original y la señal filtrada
% 4) Calcula un porcentaje aproximado de optimizacion de la señal
%
% NOTA:
% El "porcentaje de optimizacion" se calcula como reduccion del contenido
% de alta frecuencia usando la desviacion estandar de la primera diferencia:
%
%   optimizacion(%) = (1 - std(diff(y_filtrada)) / std(diff(y_original))) * 100
%
% Esto se interpreta como una estimacion de cuanto ruido/variacion rapida
% se redujo despues del filtrado. No es una metrica absoluta de calidad,
% sino una aproximacion util para comparar antes vs. despues.

clear; clc; close all;

%% Verificacion de archivos
if ~isfile('datos_x.csv')
    error('No se encontro el archivo datos_x.csv en la carpeta actual.');
end

if ~isfile('datos_y.csv')
    error('No se encontro el archivo datos_y.csv en la carpeta actual.');
end

if ~isfile('MovAvgMain.m')
    error('No se encontro main.m en la carpeta actual.');
end

if ~isfile('MovAvg.m')
    error('No se encontro Filtro.m en la carpeta actual.');
end

%% Carga de datos
x_tbl = readtable('datos_x.csv');
y_tbl = readtable('datos_y.csv');

x = x_tbl{:,1};
y = y_tbl{:,1};

x = x(:);
y = y(:);

if isempty(x) || isempty(y)
    error('Alguno de los vectores esta vacio.');
end

if length(x) ~= length(y)
    error('Los vectores x e y no tienen la misma longitud. x=%d, y=%d', length(x), length(y));
end

%% Aplicacion del filtro
% La funcion main(v) devuelve una salida con longitud menor
% porque usa una ventana de 3 datos y empieza a entregar salida
% a partir del tercer dato valido.
y_filtrada = MovAvgMain(y);

% Alineacion del tiempo con la salida filtrada
% Si todos los datos de y son mayores a 0, la salida arranca en la muestra 3.
x_filtrada = x(3:end);

% Ajuste de seguridad por si la funcion main devuelve una longitud distinta
n = min(length(x_filtrada), length(y_filtrada));
x_filtrada = x_filtrada(1:n);
y_filtrada = y_filtrada(1:n);

y_original_alineada = y(3:2+n);

%% Metricas
% 1) Reduccion de variacion rapida (aproximacion a reduccion de ruido)
hf_original = std(diff(y_original_alineada));
hf_filtrada = std(diff(y_filtrada));

optimizacion_pct = (1 - (hf_filtrada / hf_original)) * 100;

% 2) Variacion total
std_original = std(y_original_alineada);
std_filtrada = std(y_filtrada);

% 3) Error entre original y filtrada
rmse_original_vs_filtrada = sqrt(mean((y_original_alineada - y_filtrada).^2));

%% Resultados en consola
fprintf('\n===== RESULTADOS DE LA PRUEBA =====\n');
fprintf('Muestras originales: %d\n', length(y));
fprintf('Muestras filtradas : %d\n', length(y_filtrada));
fprintf('STD original       : %.6f\n', std_original);
fprintf('STD filtrada       : %.6f\n', std_filtrada);
fprintf('HF original        : %.6f\n', hf_original);
fprintf('HF filtrada        : %.6f\n', hf_filtrada);
fprintf('RMSE O-F           : %.6f\n', rmse_original_vs_filtrada);
fprintf('Optimizacion aprox : %.2f %%\n', optimizacion_pct);

%% Graficas
figure('Name','Prueba del filtro','NumberTitle','off');

subplot(2,1,1);
plot(x, y, 'DisplayName', 'Senal original');
hold on;
plot(x_filtrada, y_filtrada, 'LineWidth', 1.2, 'DisplayName', 'Senal filtrada');
grid on;
xlabel('Tiempo');
ylabel('Amplitud');
title('Senal original vs senal filtrada');
legend('Location', 'best');

subplot(2,1,2);
plot(x_filtrada, y_original_alineada - y_filtrada, 'DisplayName', 'Diferencia');
grid on;
xlabel('Tiempo');
ylabel('Error');
title(sprintf('Diferencia original-filtrada | Optimizacion aprox = %.2f %%', optimizacion_pct));

%% Figura adicional: comparacion de primeras diferencias
figure('Name','Comparacion de variacion rapida','NumberTitle','off');
plot(x_filtrada(2:end), diff(y_original_alineada), 'DisplayName', 'diff(original)');
hold on;
plot(x_filtrada(2:end), diff(y_filtrada), 'LineWidth', 1.2, 'DisplayName', 'diff(filtrada)');
grid on;
xlabel('Tiempo');
ylabel('Primera diferencia');
title('Comparacion de contenido de alta frecuencia');
legend('Location', 'best');
