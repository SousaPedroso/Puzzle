<h1 align="center">Solução de quebra-cabeças através de buscas cegas</h1> 

<p align="center">
    <a href="#--introdução">Introdução</a> |
    <a href="#--sobre">Sobre</a> |
    <a href="#--proposta">Proposta</a> |
    <a href="#--execução">Execução</a> |
    <a href="#--conclusão">Conclusão</a> |
    <a href="#--licença">Licença</a>
</p>

## [](https://github.com/SousaPedroso/Puzzle#--introdução)💻 Introdução

<p>
    Inteligência Artificial tem sido muito utilizada para a resolução de diversos problemas, desde muitos complexos, como <a href="https://www.poder360.com.br/coronavirus/biontech-cria-sistema-para-identificar-variantes-da-covid/">reconhecimento de variantes de alto risco da covid-19</a> até problemas mais simples, como a resolução de quebra-cabeças.
</p>
<p>
    Apesar disso, as técnicas e abordagens são muito semelhantes, diferenciando (algumas situações) os algoritmos e suas técnicas necessárias. Redes Neurais, por exemplo, poderiam resolver o quebra-cabeças, mas exigem uma enorme quantidade de dados, a ter uma maior velocidade após aprender. Neste projeto, são implementadas a <a href="https://pt.wikipedia.org/wiki/Busca_em_profundidade">busca em profundidade (dfs)</a> e a <a href="https://pt.wikipedia.org/wiki/Busca_em_largura">busca em largura (bfs)</a>, as quais apesar de não exigirem uma enorme quantidade de dados, a longo prazo, podem ser menos eficientes, mas <i>resolvem</i> o problema.
</p>

## [](https://github.com/SousaPedroso/Puzzle#--sobre)🧩 Sobre o projeto

<p>
    O trabalho proposto na disciplina de Inteligência Artifical pela professora Dra. <a href="http://buscatextual.cnpq.br/buscatextual/visualizacv.do;jsessionid=857482D7CE6ADB6A9CAC7690EF92F7D3.buscatextual_4">Cláudia Aparecida Martins</a> consiste em resolver um quebra-cabeças de 8 peças, com um espaço em branco para deslocar as peças, movendo cada peça possível a partir de um estado inicial até o estado desejado (final). Um exemplo disso está na imagem abaixo, com respectivamente o estado inicial e o final.
</p>

![](https://github.com/SousaPedroso/Puzzle/blob/master/images/puzzleStates.PNG)
<p>
    Além disso, deseja-se saber qual foi a solução encontrada (passos) e o custo da busca em número de passos, sendo que não podem haver repetições de estados do quebra-cabeças.
</p>
<p>
    A diferença entre essas duas últimas é que o custo da solução é quantos passos mínimos são necessários para que <i>seja possível</i> alcançar a solução, enquanto o custo da busca representa o número total de passos até encontrar a solução.
</p>

## [](https://github.com/SousaPedroso/Puzzle#--proposta)💡 Proposta

<p>
    Tanto a implementação da <i>bfs</i> quanto da <i>dfs</i> podem ser feitas de diferentes formas considerando diferentes situações. Um dos principais pontos a serem observados e que precisa de atenção é a <i>não repetição</i> dos estados, para evitar ficar preso na busca e não encontrar uma solução. Esse ponto resolvi da seguinte forma:
</p>

- Cada estado da matriz é uma string.
- Todos os estados (únicos) são armazenados.
- A busca ocorre somente se ao mover uma peça o estado já não ocorreu antes.
- O estado considera as peças como se o quebra-cabeças fosse _achatado_ (1-dimensão).

<p>
    Uma outra solução poderia ser utilizar o <a href="https://codeforces.com/blog/entry/60442">hash de cada string, ao invés da string</a> (conceitos mais pesados), a partir de um número primo muito grande, para manter O(1) cada consulta de um estado, mas para cada movimento de peças seria preciso calcular novamente o hash, então optei por armazenar as strings, pois a partir do estado inicial, é preciso trocar somente duas posições para o novo estado, além de que a consulta não é tão problemática (<a href="https://www.cplusplus.com/reference/set/set/find/">log n</a>).
</p>

<p>
    Nesse caso, muito mais memória vai ser preciso, mas a complexidade do código fica um pouco menor. Futuramente será implantando o uso de hash 😃. 
</p>

## [](https://github.com/SousaPedroso/Puzzle#--execução)🛠 Execução

<p>
    O problema foi solucionado utilizando C++17, considere utilizar a mesma versão para não ter comportamentos inesperados para compilar.
</p>
<p>
    O programa foi desenvolvido no windows, apesar de testado para compilar UNIX, algumas distribuições podem ter algum erro. Os usuários de MAC que tiverem problemas também podem criar uma <a href="https://github.com/SousaPedroso/Puzzle/issues">issue</a> alertando.
</p>


## [](https://github.com/SousaPedroso/Puzzle#--conclusão)🤔 Conclusão

<p>
    A busca em profundidade demonstrou ser bem mais problemática que a busca em largura, isto devido a ser um algoritmo guloso, buscando cada vez "mais fundo" a solução e precisando voltar um estado ao verificar que ele já foi.
</p>

<p>
    A busca em largura devido a checar cada possibilidade de movimento, apesar da expansão, consegue "rapidamente" determinar uma solução, por não explorar caminhos que podem não levar a lugar algum.
</p>

## [](https://github.com/SousaPedroso/Puzzle#--licença)📝 Licença

<p>
    Distribuído sobre a licença MIT. Veja <a href="https://github.com/SousaPedroso/Puzzle/blob/master/LICENSE">LICENSE</a> para mais informações.
</p>