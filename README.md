<h1 align="center">Solução de quebra-cabeças através de buscas cegas</h1>

<p align="center">
    <img alt="Puzzle console" width="200" height="200" src="https://github.com/SousaPedroso/Puzzle/blob/master/images/puzzleExample.PNG">
</p>

<p align="center">
    <a href="#-introdução">Introdução</a> |
    <a href="#-sobre-o-projeto">Sobre</a> |
    <a href="#-proposta">Proposta</a> |
    <a href="#-execução">Execução</a> |
    <a href="#-conclusão">Conclusão</a> |
    <a href="#-licença">Licença</a>
</p>

## [](https://github.com/SousaPedroso/Puzzle/tree/master#-introdução)💻 Introdução

<p>
    Inteligência Artificial tem sido muito utilizada para a resolução de diversos problemas, desde muitos complexos, como <a href="https://www.poder360.com.br/coronavirus/biontech-cria-sistema-para-identificar-variantes-da-covid/">reconhecimento de variantes de alto risco da covid-19</a> até problemas mais simples, como a resolução de quebra-cabeças.
</p>
<p>
    Apesar disso, as técnicas e abordagens são muito semelhantes, diferenciando (algumas situações) os algoritmos e suas técnicas necessárias. Redes Neurais, por exemplo, poderiam resolver o quebra-cabeças, mas exigem uma enorme quantidade de dados, a ter uma maior velocidade após aprender. Neste projeto, são implementadas a <a href="https://pt.wikipedia.org/wiki/Busca_em_profundidade">busca em profundidade (dfs)</a> e a <a href="https://pt.wikipedia.org/wiki/Busca_em_largura">busca em largura (bfs)</a>, as quais apesar de não exigirem uma enorme quantidade de dados, a longo prazo, podem ser menos eficientes, mas <i>resolvem</i> o problema.
</p>

## [](https://github.com/SousaPedroso/Puzzle/tree/master#-sobre-o-projeto)🧩 Sobre o projeto

<p>
    O trabalho proposto na disciplina de Inteligência Artifical pela professora Dra. <a href="http://lattes.cnpq.br/0252766947347684">Cláudia Aparecida Martins</a> consiste em resolver um quebra-cabeças de 8 peças, com um espaço em branco para deslocar as peças, movendo cada peça possível a partir de um estado inicial até o estado desejado (final). Um exemplo disso está na imagem abaixo, com respectivamente o estado inicial e o final.
</p>

<p align="center">
    <img alt="Puzzle console" src="https://github.com/SousaPedroso/Puzzle/blob/master/images/puzzleStates.PNG">
</p>

<p>
    Além disso, deseja-se saber qual foi a solução encontrada (passos) e o custo da busca em número de passos, sendo que não podem haver repetições de estados do quebra-cabeças.
</p>
<p>
    A diferença entre essas duas últimas é que o custo da solução é quantos passos mínimos são necessários para que <i>seja possível</i> alcançar a solução, enquanto o custo da busca representa o número total de passos até encontrar a solução.
</p>

## [](https://github.com/SousaPedroso/Puzzle/tree/master#-proposta)💡 Proposta

<p>
    Tanto a implementação da <i>bfs</i> quanto da <i>dfs</i> podem ser feitas de diferentes formas considerando diferentes situações. Um dos principais pontos a serem observados e que precisa de atenção é a <i>não repetição</i> dos estados, para evitar ficar preso na busca e não encontrar uma solução. Esse ponto resolvi da seguinte forma:
</p>

- Cada estado da matriz é uma string.
- Todos os estados (únicos) são armazenados.
- A busca ocorre somente se ao mover uma peça o estado já não ocorreu antes.
- O estado considera as peças como se o quebra-cabeças fosse _achatado_ (1-dimensão).

## [](https://github.com/SousaPedroso/Puzzle/tree/master#-execução)🛠 Execução

<p>
    O problema foi solucionado utilizando C++17, considere utilizar a mesma versão para não ter comportamentos inesperados para compilar.
</p>
<p>
    O programa foi desenvolvido no windows, apesar de testado para compilar UNIX, algumas distribuições podem ter algum erro. Os usuários de MAC que tiverem problemas também podem criar uma <a href="https://github.com/SousaPedroso/Puzzle/issues">issue</a> alertando.
</p>


## [](https://github.com/SousaPedroso/Puzzle/tree/master#-conclusão)🤔 Conclusão

<p>
    A busca em profundidade demonstrou ser bem mais eficiente que a busca em largura, isto pois não precisa armazenar toda a árvore de estados para checar a solução.
</p>

<p>
    A busca em largura devido a checar cada possibilidade de movimento, consegue determinar a solução com menor custo, mas demora muito mais que a busca em profundidade para isso.
</p>

## [](https://github.com/SousaPedroso/Puzzle/tree/master#-licença)📝 Licença

<p>
    Distribuído sobre a licença MIT. Veja <a href="https://github.com/SousaPedroso/Puzzle/blob/master/LICENSE">LICENSE</a> para mais informações.
</p>
