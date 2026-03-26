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

