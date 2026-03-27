datax = readtable('datos_x.csv').x;
datay = readtable('datos_y.csv').y;
num_datos = length(datax);
%%LwPassFill
ALPHA = 0.9
y_k_e = 0;
y_filtered = [ ];
for k = 1:1:num_datos
    y_k = datay(k);
    y_k_e = y_k*(1-ALPHA) + y_k_e*(ALPHA);
    y_filtered = [y_filtered y_k_e];
end

figure

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