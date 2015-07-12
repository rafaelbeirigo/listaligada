set term png enhanced size 1366,768 font ",20"
set encoding utf8

experimentosimples = "resultadolistasimple08julio"
experimentodupla = "resultadolistadupla08julio"

set output "slides/fig/resultadocompara08julio.png"

titulo = "Listas Simples e Dupla - Comparação"

set rmargin 4
set title titulo
set xlabel "Quantidade de nós presentes na lista"
set ylabel "Tempo (s)"

plot experimentosimples.".txt" w l ls 1 lc 1 lw 2title "Lista Simples", \
     experimentodupla.".txt" w l ls 1 lc 3 lw 2 title "Lista Dupla"
