#!/usr/bin/env bash


ruta='/home/marln/Documentos/C/TalleresProgsisOtros/tareaServidorCliente/archivos/'


h_server(){
	./servidor/file_server -h
}

h_client(){
	./file_client -h
}

window_server1(){
	cd servidor
	./file_server 8080& &> result_server1.txt
	cd ..
}

kill1(){
	kill -2 $(pidof ./file_server)
}

kill2(){
	kill -2 $(pidof ./file_client)
}

server2(){
	cd servidor
	./file_server -d -j 15 8081 &> result_server2.txt
	cd ..
}

client(){
	printf '14.png\nSTART\n15.png\nSTART\nCHAO\n' | ./file_client 127.0.0.1 8081 &> result.txt
	printf '16.png\nSTART\n17.png\nSTART\nCHAO\n' | ./file_client 127.0.0.1 8081 &> result2.txt
	printf 'x.png\ny.png\nCHAO\n' | ./file_client 127.0.0.1 8081 &> result3.txt
}

results(){
	echo "Imprimiento resultado de primer ejecucion de server 1"
	cat servidor/result_server1.txt
	echo "Imprimiendo resultado de primer ejecucion de server 2"
	cat servidor/result_server2.txt
	echo "Imprimiendo resultado de primer cliente"
	cat result.txt
	echo "Imprimiento resultado de segundo cliente"
	cat result2.txt
	echo "Imprimiendo resultado de cliente dummy"
	cat result3.txt	
}

compilation(){
    echo "Compilando su programa"
    counter=0
	echo 'Haciendo make primera vez'
	make
    
	for d in *.h ;
        do  
            [ -f "$d" ] || continue  
            if [ "$d" != sha1.h -a "$d" != sha256.h -a "$d" != md5.h -a "$d" != csapp.h ]; 
                then 
                    (echo '#define TUM3 1024' | cat - "$d" > temp && mv temp "$d") && let counter++;
            fi
        done
	for d in ./*/ ; 
		do for h in "$d"*.h ; 
			do
                [ -f "$h" ] || continue
                if [ "$h" != "$d"sha1.h -a "$h" != "$d"sha256.h -a "$h" != "$d"md5.h -a "$h" != "$d"csapp.h ]; 
                    then  
                        (echo '#define TUM3 1024' | cat - "$h" > temp && mv temp "$h") && let counter++;
                fi
		    done
	    done
    if [ $counter = 0 ];
        then
            echo 'Este usuario no tiene archivos .h, no haciendo make'
        else
            echo 'Haciendo make alterando .h' && make;
    fi 
	echo 'Usando make clean'
	make clean 
	echo 'Haciendo make otra vez'
	make
	
}

preparing(){
	echo "Preparando archivos necesarios"
	mkdir servidor
	mv file_server servidor/
	cp $ruta*.png servidor/
	touch result.txt result2.txt result3.txt servidor/result_server1.txt servidor/result_server2.txt
}

finalize(){
	kill1
	kill2
	kill2
	kill2
	results
	echo "Pruebas Finalizadas"
	make clean
	#rm -r servidor
	rm result.txt result2.txt result3.txt
}

execute(){
	echo "Ejecutando programas"
	h_server
	h_client
	window_server1
	kill1
	sleep 5
	server2
	client
	sleep 5 && finalize
}



compilation
preparing
execute

