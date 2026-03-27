datax = readtable('datos_x.csv').x;
datay = readtable('datos_y.csv').y;
num_datos = length(datax);
%%KalmanFilt
A = 1;
H = 1;
xk = 1000;
xk_p = 0;
Pk = 500;
Pk_p = 0;
R = 10;
K = 0;

Q = 0.01; % Evita que el filtro se "cierre"
y_filtered = zeros(1, num_datos); 

for i = 1:num_datos
    % 1. Predict
    xk_p = A * xk;
    Pk_p = A * Pk * A' + Q;
    
    % 2. Update (Gain)
    K = Pk_p * H' / (H * Pk_p * H' + R); % Usar / en lugar de inv() es más eficiente
    
    % 3. Correct
    xk = xk_p + K * (datay(i) - H * xk_p);
    Pk = (1 - K * H) * Pk_p;
    
    % 4. Store
    y_filtered(i) = xk;
end


figure(1)

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

% 1. Definir el punto de inicio (ignorar el primer 10% por el transitorio)
n = length(datay);
recorte = round(n * 0.1); 
if recorte == 0, recorte = 1; end % Seguridad para señales cortas

% 2. Crear el índice de comparación (del recorte al final)
idx = recorte:n;

% 3. Calcular varianzas solo en ese rango
var_ruidosa  = var(datay(idx));
var_filtrada = var(y_filtered(idx)); % Usa y_filtered o y_lpf según tu filtro

% 4. Métrica de Eficiencia: Porcentaje de Ruido Eliminado (PRE)
eficiencia_prr = (1 - (var_filtrada / var_ruidosa)) * 100;

% 5. Mostrar resultado rápido
fprintf('--- Resultado de Eficiencia ---\n');
fprintf('Ruido eliminado: %.2f%%\n', eficiencia_prr);

% 6. Visualización del "Termómetro"
figure('Name', 'Eficiencia del Filtro', 'Color', 'w');
bar(eficiencia_prr, 'FaceColor', [0.2 0.6 0.5]);
ylabel('Porcentaje (%)');
ylim([-20 100]); % Permite ver si el resultado es negativo
grid on;
title(['Eficiencia Concreta: ', num2str(eficiencia_prr, '%.2f'), '%']);
set(gca, 'XTickLabel', {'Reducción de Ruido'});