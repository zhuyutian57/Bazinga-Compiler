from graphviz import Digraph

g = Digraph(
    name = 'architecture',
    filename = 'architecture',
    directory = '../images',
    format = 'png',
    engine = 'sfdp'
    )

g.attr('node', shape = 'ellipse')
g.node(name = 'Source Codes')

g.attr('node', shape = 'box')
g.node(name = 'Symbol Table')
g.node(name = 'Lexer')
g.node(name = 'Parser')
g.node(name = 'Semantic Analyzer')
g.node(name = 'Intermediate Code Generator')
g.node(name = 'Back End')

g.edge('Source Codes', 'Lexer')
g.edge('Lexer', 'Parser', label = 'Token Stream')
g.edge('Parser', 'Semantic Analyzer', label = 'Syntax Tree')
g.edge('Semantic Analyzer', 'Intermediate Code Generator',
        label = 'Syntax Tree')
g.edge('Intermediate Code Generator','Back End',
        label = 'Intermediate Representation')

g.attr('edge', dir = 'both')
g.edge('Source Codes', 'Symbol Table')
g.edge('Lexer', 'Symbol Table')
g.edge('Parser', 'Symbol Table')
g.edge('Semantic Analyzer', 'Symbol Table')
g.edge('Intermediate Code Generator','Symbol Table')
g.edge('Back End', 'Symbol Table')

#g.view()
g.render()
