#!/usr/bin/env bash

sha1=da442ba8718f7e586ee7df888fd6add708f03ff4
md5=889e807fdfb3df5936afb90277951a50
sha256=47a74a2ae284e5a65ae1533ed0af1611fe5fd91f1f0f871e0cdf9121ee59b2ae
file=jdk-12.0.2_linux-x64_bin.deb
dummy=estearchivonidechisteexistesiestAesporquesetomAronlamolestiadecrearlo.txt
comando=curl
general=jdk12-
extension=.txt
nSHA1=sha1
nSHA256=sha256
nMD5=md5
fileSHA1=$general$nSHA1$extension
fileSHA256=$general$nSHA256$extension
fileMD5=$general$nMD5$extension

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

searching(){
    echo "-----------------------------------------------------------------"
    echo "-----------------------------------------------------------------"
    echo "Buscando archivo de prueba " $file
    
    if test -f "$file" ;
        then 
            echo "Archivo " $file "existe";
        else
            echo "Archivo " $file "no existe, se tratara de descargar con el comando curl"
            echo "Verificando que comando " $comando " se encuentra instalado en su maquina"
            if ! command -v $comando &> /dev/null ;
                then
                    echo "Comando " $comando "no se encuentra instalado en su maquina"
                    echo "Este comando sirve para descargar el archivo de prueba " $file ", instale usando:"
                    echo "sudo apt install " $comando
                    echo "No se puede hacer las pruebas sin archivo de prueba, descargue el archivo " $file " de la pagina de oracle o instale el comando curl para reintentar la descarga"
                    exit
                else 
                    echo "Comando " $comando "se encuentra instalado en su computadora"
                    echo "Descargando archivo " $file
                    curl -L https://www.dropbox.com/s/eeu4hm38e5a7fil/jdk-12.0.2_linux-x64_bin.deb?dl=0 --output $file
            fi
    fi

    echo "Las pruebas de su programa seran realizados con el archivo: " $file
}

creating(){
    echo "-----------------------------------------------------------------"
    echo "-----------------------------------------------------------------"
    echo "Creando archivos que van a contener los hashes de sha1, md5 y sha256 correspondientes para el archivo " $file
    echo "Creando archivo " $fileSHA1
    echo $sha1 > $fileSHA1
    echo "Creando archivo " $fileMD5
    echo $md5 > $fileMD5
    echo "Creando archivo " $fileSHA256
    echo $sha256 > $fileSHA256
}

testing(){
    echo "-----------------------------------------------------------------"
    echo "-----------------------------------------------------------------"
    echo "Hora de las pruebas de estres de su programa"
    echo "Ejecutando comportamientos esperados"
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -h"
    ./check_hash -h
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash" $file
    ./check_hash $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA1 $file
    ./check_hash -a $nSHA1 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nMD5 $file
    ./check_hash -a $nMD5 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA256 $file
    ./check_hash -a $nSHA256 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA1 "-c" $sha1 $file
    ./check_hash -a $nSHA1 -c $sha1 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nMD5 "-c" $md5 $file
    ./check_hash -a $nMD5 -c $md5 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA256 "-c" $sha256 $file
    ./check_hash -a $nSHA256 -c $sha256 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA1 "-f" $fileSHA1 $file
    ./check_hash -a $nSHA1 -f $fileSHA1 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nMD5 "-f" $fileMD5 $file
    ./check_hash -a $nMD5 -f $fileMD5 $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA256 "-f" $fileSHA256 $file
    ./check_hash -a $nSHA256 -f $fileSHA256 $file
    echo "-----------------------------------------------------------------"
    echo "-----------------------------------------------------------------"
    echo "Ejecutando ahora comportamientos erroneos, para ver como controlan los errores"
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash"
    ./check_hash
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a -f -c"
    echo "La falta de argumentos lo maneja el getopt, pero igual hay que revisar si todo esta ok"
    ./check_hash -a -f -c 
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash" $dummy
    echo "Probando que hace si archivo no existe"
    ./check_hash $dummy
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a blowfish" $file
    echo "Tiene dos opciones, o ignora el argumento erroneo y ejecuta con hash sha256, o muestra un mensaje de error y detiene la ejecucion" 
    ./check_hash -a blowfish $file
    echo "*****************************************************************"
    echo "Ejecutando ./check_hash -a" $nSHA256 "-f" $dummy $file
    echo "Probando que hace si archivo donde esta hash a comparar no existe"
    ./check_hash -a $nSHA256 -f $dummy $file
}

compilation
searching
creating
testing