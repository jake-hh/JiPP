
Names=('Adam' 'Jakub' 'Stefan' 'Alicja' 'Maurycy' 'Zygmunt' 'Marzena' 'Maciej' 'Marek' 'Mateusz')
Surnames=('Nowak' 'Kowalski' 'Buk' 'Sodowy' 'Wysocki' 'Pien' 'Kiszka' 'Nienacki' 'Mickiewicz' 'Bębno')
Streets=('Kasztanowa' 'al.Mickiewicza' 'Szwedzka' 'Lubomirska' 'Floriańska' 'Lipowa' 'al.Pokoju' 'Wielicka' 'Junacka' 'Praska')

function rid {
	echo $(($RANDOM % 10))
}

for i in {1..50}
do
	echo "${Names[`rid`]} ${Surnames[`rid`]} $(($RANDOM % 5 + 2002)) ${Streets[`rid`]} $(($RANDOM % 4 * 400))"
done