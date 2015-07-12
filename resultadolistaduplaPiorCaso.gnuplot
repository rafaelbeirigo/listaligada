experimento = "resultadolistaduplaPiorCaso-slides"
titulo = "Lista Dupla - Pior Caso"
legenda = ""

set term png enhanced size 1366,768 font ",20"
set encoding utf8

set output "slides/fig/".experimento.".png"

set rmargin 4
set title titulo
set xlabel "Quantidade de nós presentes na lista"
set ylabel "Tempo (s)"

plot experimento.".txt" with lines lc 3 lw 2 title legenda
