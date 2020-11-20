#bin/zsh
first(){
	echo 'Haciendo make primera vez'
	make
	make tail
	make head
	for d in ./*.h ; 
                do  (echo '#define TUM3 1024' | cat - "$d" > temp && mv temp "$d")
        done
	for d in ./*/ ; 
		do for h in ./*.h ; 
			do  (echo '#define TUM3 1024' | cat - "$h" > temp && mv temp "$h")
		done
	done
	echo 'Haciendo make alterando .h'
	make 
	make tail
	make head
	echo 'Usando make clean'
	make clean 
	echo 'Haciendo make otra vez'
	make
	make tail
	make head
	echo 'Probando programa head con opcion -h y enviando otros parametros'
	./head -n 20 -h a.c
	echo 'Probando programa head sin opcion -n'
	./head a.c
	echo 'Probando programa head usando opcion -n'
	./head -n 5 a.c
	echo 'Probando programa head con opcion -n y enviando numeros negativos'
	./head -n -5 a.c
	echo 'Probando programa head sin enviar archivo'
	./head -n 20 
	./head 
	echo 'Probando programa tail con opcion -h y enviando otros parametros'
	./tail -n 20 -h a.c
	echo 'Probando programa tail sin opcion -n'
        ./tail a.c
	echo 'Probando programa tail usando opcion -n'
        ./tail -n 5 a.c 
	echo 'Probando programa tail con opcion -n y enviando numeros negativos'
        ./tail -n -5 a.c
	echo 'Probando programa tail sin enviar archivo'
        ./tail -n 20 
        ./tail 
}

first
