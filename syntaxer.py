from lexer import Token
from nodes import *

class SyntaxAnalyzer:
    def __init__(self, tokens: list) -> None:
        self.tokens = tokens
        self.pos = 0
        self.level = 0

    def match(self, *expected) -> Token | None:
        """Проверяет, соответствует ли текущий токен одному из ожидаемых типов."""
        if self.pos < len(self.tokens):
            currentToken = self.tokens[self.pos]
            if currentToken.type in expected:
                self.pos += 1
                return currentToken
        return None

    def require(self, *expected) -> Token:
        """Требует токен из ожидаемых типов. В случае отсутствия вызывает исключение."""
        token = self.match(*expected)
        if not token:
            raise SyntaxError(f'expected {expected[0]} on position {self.pos}')
        return token

    def parseValue(self) -> ExpressionNode:
        """Парсит значения (числа, переменные и строки)."""
        return ValueNode(self.require('NUMBER', 'IDENTIFIER', 'STRING'))

    def parseFunc(self) -> ExpressionNode:
        """Парсит вызовы функций."""
        function = self.match('IDENTIFIER')  # Здесь предполагаем, что функция - это идентификатор
        if function:
            self.require('SEPARATOR', '(')
            operand = self.parseFormula()
            self.require('SEPARATOR', ')')
            return UnarOperatorNode(function, operand)
        raise SyntaxError(f'expected function identifier on position {self.pos}')

    def parseLog(self) -> ExpressionNode:
        """Парсит логические операции."""
        return UnarOperatorNode(self.require('KEYWORD', 'LOGICAL_OP'), self.parseFormula())

    def parseBlock(self) -> ExpressionNode:
        """Парсит блоки кода, например, условные операторы или циклы."""
        blockToken = self.match('KEYWORD')
        if blockToken:
            block = BlockNode(blockToken)
            self.require('SEPARATOR', '{')
            while not self.match('SEPARATOR', '}'):
                expression = self.parseExpression()
                block.add_node(expression)
            return block
        return None

    def parseParenthesis(self) -> ExpressionNode:
        """Парсит выражения в скобках."""
        if self.match('SEPARATOR', '('):
            formulaNode = self.parseFormula()
            self.require('SEPARATOR', ')')
            return formulaNode
        return self.parseValue()

    def parseFormula(self) -> ExpressionNode:
        """Парсит математические выражения (с бинарными операциями)."""
        leftNode = self.parseParenthesis()
        operator = self.match('OPERATOR')
        while operator:
            rightNode = self.parseParenthesis()
            leftNode = BinOperatorNode(operator, leftNode, rightNode)
            operator = self.match('OPERATOR')
        return leftNode

    def parseExpression(self) -> ExpressionNode:
        """Парсит выражения, включая присваивания, вызовы функций, операторы и блоки."""
        
        # Пропускаем пустые строки и пробелы
        while self.match('NEWLINE') or self.match('SKIP'):
            print('Успешно скипнули пробел')
            continue

        # Проверка на идентификатор (переменная) для возможного присваивания
        if self.match('IDENTIFIER'):
            variableNode = self.parseValue()  # Получаем значение переменной
            assignOperator = self.match('OPERATOR', '=')  # Проверка на оператор присваивания '='
            
            if assignOperator:
                formulaNode = self.parseFormula()  # Разбор выражения для присваивания
                binaryNode = BinOperatorNode(assignOperator, variableNode, formulaNode)  # Создание узла для бинарной операции
                print('успех идентификатор')
                return binaryNode
            else:
                self.pos -= 1  # Отменяем матч, так как присваивание не найдено
                return self.parseFormula()  # Возвращаем просто выражение, если присваивания нет

        # Обработка ключевого слова RETURN
        elif self.match('KEYWORD', 'RETURN'):
            print('Успех ретёрн')
            return self.parseFunc()  # Вызов функции для парсинга возвращаемого значения

        # Обработка блоков кода (например, IF, ELSE или просто блок)
        elif self.match('KEYWORD', 'IF') or self.match('KEYWORD', 'ELSE'):
            print('успех блока')
            return self.parseBlock()  # Парсим блок кода (например, условный оператор)

        # Обработка открывающей скобки { как начала блока кода
        elif self.match('SEPARATOR', '{'):
            blockNode = BlockNode(Token('BLOCK', '{', self.tokens[self.pos].line, self.tokens[self.pos].column))
            self.require('NEWLINE')  # Ожидаем новый перевод строки после открывающей скобки
            self.level += 1  # Увеличиваем уровень вложенности
            while self.match('NEWLINE'):  # Пропускаем пустые строки и начинаем разбор выражений внутри блока
                expression = self.parseExpression()  # Парсим выражение внутри блока
                blockNode.add_node(expression)  # Добавляем его в блок
            self.level -= 1  # Уменьшаем уровень вложенности
            self.require('SEPARATOR', '}')  # Ожидаем закрывающую скобку блока
            print('успех скобки')
            return blockNode  # Возвращаем узел блока

        # Если встретился литерал (число, строка, булево значение), то парсим его как выражение
        elif self.match('NUMBER', 'STRING', 'BOOLEAN'):
            self.pos -= 1  # Отменяем матч, если ожидаем число, строку или булево значение
            print('успех литерал')
            return self.parseFormula()  # Разбор общего выражения для данных типов

        # Если встретился оператор, парсим бинарное выражение
        elif self.match('OPERATOR'):
            operator = self.match('OPERATOR')
            leftNode = self.parseFormula()  # Парсим левую часть выражения
            rightNode = self.parseFormula()  # Парсим правую часть выражения
            binaryNode = BinOperatorNode(operator, leftNode, rightNode)  # Создаем бинарный узел
            print('успех оператор')
            return binaryNode

        else:
            raise SyntaxError(f"Unexpected token at position {self.pos}")



    def parse(self) -> StatementNode:
        """Основная функция для парсинга кода."""
        root = StatementNode()

        while self.pos < len(self.tokens):
            expression = self.parseExpression()
            self.require('NEWLINE')  # Пропускаем новую строку после каждого выражения
            root.add_node(expression)

        return root

    def getTextNode(self, node: ExpressionNode) -> str:
        """Генерирует строку Python кода из узла синтаксического дерева."""
        nodeType = type(node)

        if nodeType == ValueNode:
            return f'{node.value.value}'
        elif nodeType == BinOperatorNode:
            return f'{self.getTextNode(node.left)} {node.operator.value} {self.getTextNode(node.right)}'
        elif nodeType == UnarOperatorNode:
            return f'{node.operator.value}({self.getTextNode(node.operand)})'
        elif nodeType == BlockNode:
            res = f'{node.keyword.value}:\n'
            for line in node.body:
                res += f'    {self.getTextNode(line)}\n'
            return res
        elif nodeType == ElseNode:
            res = f'{node.keyword.value}:\n'
            for line in node.body:
                res += f'    {self.getTextNode(line)}\n'
            return res

    def getTextTree(self, root: StatementNode) -> str:
        """Генерирует Python код из корня синтаксического дерева."""
        textTree = ''
        for line in root.statements:
            if line:
                textTree += self.getTextNode(line)
        return textTree
