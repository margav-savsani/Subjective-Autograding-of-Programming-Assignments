import unittest
import algo1

# pairs of input lines and expected output lines
lineTestCases = [
    [ 
        r'proc test-algo(A, abc)',
        r'\Procname{\proc{test-algo}(\id{A}, \id{abc})}'
    ],
    [
        r'for j <- 2 to A.length do',
        r'\zi\For \id{j} $\leftarrow$ 2 \To \attrib{A}{length} \Do'
    ],
]


keywordsToTex = {
    'for'    : r'\For'        ,     'if'     : r'\If'          , 
    'end'    : r'\End'        ,     'then'   : r'\Then'        , 
    'while'  : r'\While'      ,     'do'     : r'\Do'          ,  
    'to'     : r'\To'         ,     'by'     : r'\By'          , 
    'downto' : r'\Downto'     ,     'repeat' : r'\Repeat'      , 
    'until'  : r'\Until'      ,     'elseif' : r'\Elseif'      ,
    'elsif'  : r'\Elseif'     ,     'return' : r'\Return'      , 
    'error'  : r'\Error'      ,     'nil'    : r'\const{nil}'  , 
    'true'   : r'\const{true}',     'false'  : r'\const{false}'
}

opsToTeX = {
    '<-' : r'\leftarrow' ,      '->' : r'\rightarrow',      '==' : r'\isequal' ,
    '<=' : r'\leq'       ,      r'>=' : r'\geq'        ,     '>' : '>'          , 
    '<' : '<'            ,      '!=' : r'\neq'       ,      '=' : r'\eq'       , 
    '...' : r'\threedots',      '..' : r'\twodots'
}

class TestAlgo(unittest.TestCase):

    def testComment(self):
        line = "abc // def"
        self.assertEqual(algo1.processComment(line), "\Comment abc // def")
    
    def testKeywords(self):
        for word in keywordsToTex.keys():
            self.assertEqual(algo1.processWords(word), keywordsToTex[word])

    def testOps(self):
        for word in opsToTeX.keys():
            with self.subTest(word):
                self.assertEqual(algo1.processOps(word), '$' + opsToTeX[word] + '$')            
    
    def testMath(self):
        line = "$abc <- abc[i] * 2$"
        self.assertEqual(algo1.processMath(line), "$\id{abc} $\leftarrow$ \id{abc}[\id{i}] * 2$")

    def testLine(self):	
        for test in lineTestCases:
            with self.subTest(test[0]):
                self.assertEqual(algo1.processLine(test[0]), test[1])

if __name__ == '__main__':
	unittest.main()

