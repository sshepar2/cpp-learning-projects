set datafile separator ","
set key autotitle columnheader   # uses "snr_db" and "ber" as labels

set terminal pdfcairo enhanced color size 4,3
set output "ber_curve.pdf"

set title "Simulation BER vs SNR"
set xlabel "SNR (dB)"
set ylabel "Bit Error Rate"
set yrange [1e-6:1]
set logscale y
set format y "10^{%L}"
set grid

plot "results/ber_results.csv" using 1:2 with linespoints \
     lc rgb "#4af0a0" pt 7 ps 0.8 title "BPSK"
