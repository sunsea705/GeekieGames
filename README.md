# GeekieGames

Olá, eu me chamo Carolina. GeekieGames é uma aplicação simples escrita em C++ que gerencia questões de qualquer tema que você queira (bastando apenas os arquivos de texto, que é onde ficam as questões) dividido por categorias e dificuldade da questão (onde você entrando no modo de adminstrador pode alterar, excluir e criar essas categorias e dificuldades). 

A aplicação ainda usando uma autenticação simples com login e senha para permitir múltiplos usuários. Ele ainda consegue marcar as questões como resolvidas, de modo que você só veja questões que você ainda não terminou.

Essa aplicação é oriunda da terceira nota da minha cadeira de Linguagem de Programação, em 2018.1. Consegui receber nota 10 por ela :)

-> Observações antes de usar o programa: 

I) Extraia o arquivo "database.zip", deixe ele na mesma pasta dos códigos, pois o caminho da manipulação dos arquivos de texto é feito em cima dessa pasta e dos arquivos dentro dela.

II) ATENÇÃO! Por algum motivo obscuro NÃO TENTE EDITAR MANUALMENTE O ARQUIVO QUE CONTÉM OS LOGINS. Depois de fazer qualquer alteração no bloco de notas por exemplo, ao adicionar novos usuários, o programa salta uma linha e isso buga o código porque ele foi feito para ler apenas uma única linha de arquivo. ENTÃO NAO EDITE O ARQUIVO DE LOGIN MANUALMENTE, senao vai dar ruim.

III) Para cadastrar exercícios, voce precisa do nome e senha do administrador. O nome e a senha do administrador são "admin" e "admin" respectivamente. Sim, isso mesmo. Se quiser você pode alterar isso, mudando onde é feita a autenticação, mas faça com extrema cautela. Lembre-se que esse projeto não é um GeekieGames real ou um site do Descomplica.

IV)  A aplicação roda no terminal e foi criada em um computador com Linux, então se você tentar rodar num Windows ou Mac precisa fazer uma alteração nos códigos que são específicos para esses sistemas.
