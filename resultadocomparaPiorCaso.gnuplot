set term png enhanced size 1366,768 font ",20"
set encoding utf8

experimentosimples = "resultadolistasimplePiorCaso-slides"
experimentodupla = "resultadolistaduplaPiorCaso-slides"

set output "slides/fig/resultadocomparaPiorCaso.png"

titulo = "Listas Simples e Dupla - Pior Caso - Comparação"

set rmargin 4
set title titulo
set xlabel "Quantidade de nós presentes na lista"
set ylabel "Tempo (s)"

plot experimentosimples.".txt" w l ls 1 lc 1 lw 2title "Lista Simples", \
     experimentodupla.".txt" w l ls 1 lc 3 lw 2 title "Lista Dupla"
