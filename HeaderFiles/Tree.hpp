#pragma once
#include "JDM/JDM.hpp"

JUSING JNAMESPACE JDM;
JUSING JNAMESPACE JDM::Comp;

JSTRUCT Node {

    JINT    value       = 0;
    JINT    level       = 0;
    Node   *parent      = JNULLPTR;
    Node   *left        = JNULLPTR;
    Node   *right       = JNULLPTR;

    JDOUBLE nodeSize    = 150;
    JDOUBLE screenWidth = (1200 - 40);
    JDOUBLE xPos        = 20;
    JDOUBLE midX        = 1200 / 2;
    JDOUBLE midY        = (700 - (nodeSize)) - 20;
    JCHAR   position    = 'N';

    JSP<Button> nodeGraphics = JNULLPTR;
};

JSTRUCT NodeValue {
    Node *node = JNULLPTR;
    JCHAR position;
};

JCLASS Tree
{
JPUBLIC:
    JSTATIC JCONST std::string WindowTitle;
    JSTATIC JCONST JDM::ColorRGB backGround;
    JSTATIC JCONST JDOUBLE WIDTH;
    JSTATIC JCONST JDOUBLE HEIGHT;

    JDM::ColorRGBA ellipseColor            = {0xff, 0xff, 0xff, 0xff};
    JDM::ColorRGBA ellipseTextActiveColor  = {0x44, 0xcc, 0x44, 0xff};
    JDM::ColorRGBA ellipseTextColor        = {0x22, 0x66, 0x22, 0xff};

    JSP<Image> backgroundImage = JMS<Image>("Assets/backgroundTree.png");

    Node *rootNode = JNULLPTR;

JPROTECTED:
    JCVOID initAllObjects()
    {
        srand(std::time(nullptr));
        JTHIS->backgroundImage->setSizePos({0, 0, Tree::WIDTH, Tree::HEIGHT});
        Window::addComponents(JTHIS->backgroundImage);

        JTHIS->generateBinarySearchTree(20);
        JTHIS->recursivelyCheck(JTHIS->rootNode);
    }
    JCVOID update() { }

    JCVOID addNode(Node* node, JINT value, JCHAR position) {
        Node *newNode     = JNEW Node();
        newNode->value    = value;
        newNode->parent   = node;
        newNode->position = position;
        newNode->level    = node->level + 1;

        JIF (position == 'L')
            node->left = newNode;
        JELSE JIF (position == 'R')
            node->right = newNode;
    }

    JCVOID generateBinarySearchTree(JINT quantity) {
        // JIF (self.target)
        //     self.target.node_label.color = self.ellipseTextColor
        //     self.target = None
        // self.target = None

        JIF (JTHIS->rootNode == JNULLPTR) {
            JTHIS->rootNode = JNEW Node();
            JTHIS->rootNode->value = 50 + (Random() % 50);
            // self.allNodeSave[self.indexSave].append([self.root.value, True])
        }

        JFOR (JINT i = 0; i < quantity; i++) {
            JINT value = Random() % 100;
            NodeValue nodeVal = JTHIS->getParentAndPosition(JTHIS->rootNode, value);

            JIF (nodeVal.node == JNULLPTR || nodeVal.node->level >= 4)
                JCONTINUE;

            JTHIS->addNode(nodeVal.node, value, nodeVal.position);

            // if (position == 'R'):
            //     self.allNodeSave[self.indexSave].append([parent.right.value, False])
            // else:
            //     self.allNodeSave[self.indexSave].append([parent.left.value, False])
        }
    }

    NodeValue getParentAndPosition(Node *node, JINT value) {
        JIF (value == node->value) JRETURN {JNULLPTR, 'N'};
        JIF (value > node->value) {
            JIF (node->right == JNULLPTR)
                JRETURN {node, 'R'};
            JRETURN JTHIS->getParentAndPosition(node->right, value);
        }
        JELSE {
            JIF (node->left == JNULLPTR)
                JRETURN {node, 'L'};
            JRETURN JTHIS->getParentAndPosition(node->left, value);
        }
    }

    JCVOID recursivelyCheck(Node* node) {
        JIF (node == JNULLPTR) JRETURN;

        JTHIS->setNodeProperty(node);

        node->nodeGraphics = JMS<Button>(JTOSTR(node->value), "Assets/nodeDesign2.png");
        node->nodeGraphics->setSize({node->nodeSize, node->nodeSize});
        node->nodeGraphics->setPos({node->midX - node->nodeSize / 2, node->midY});
        node->nodeGraphics->setFontSize(28 - (4 * node->level));
        node->nodeGraphics->setBold(JTRUE);
        node->nodeGraphics->setOriginalColor(JTHIS->ellipseColor);
        node->nodeGraphics->setTextAndOpacityColor(JTHIS->ellipseTextColor);

        Window::addComponents(node->nodeGraphics);

        // node.node_label.func_binder = lambda widget = node: self.changeTarget(widget)

        // if (node is self.target):
        //     node.node_label.color = self.ellipseTextActiveColor
        // else: node.node_label.color = self.ellipseTextColor

        JTHIS->recursivelyCheck(node->left);
        JTHIS->recursivelyCheck(node->right);
    }

    JCVOID setNodeProperty(Node *node, JCBOOL anim = JFALSE) {
        node->nodeSize = 100;
        node->nodeSize -= ((node->level + 1) * 8);

        JIF (node->parent != JNULLPTR) {
            node->screenWidth = node->parent->screenWidth / 2;

            JIF (node->position == 'L')
                node->xPos = node->parent->xPos;
            JELSE JIF (node->position == 'R')
                node->xPos = node->parent->xPos + node->screenWidth;

            node->midX = (node->xPos + (node->screenWidth / 2));
            node->midY = 20 + (100 * node->level - (3 * node->level * node->level));

            // if (anim): Clock.schedule_once(lambda *_: self.addLine(node), self.animationSpeed)
            // else: self.addLine(node)
        }
        JELSE {
            node->screenWidth = 1200 - 40;
            node->xPos        = 20;
            node->midX        = 1200 / 2;
            node->midY        = 20;

            // if (anim): Clock.schedule_once(self.addRootEllipse, self.animationSpeed)
            // else: self.addRootEllipse()
        }
    }
};

JCONST std::string Tree::WindowTitle = "Tree Representation";
JCONST JDM::ColorRGB Tree::backGround = JDM::getColorFromHex("000000");
JCONST JDOUBLE Tree::WIDTH = 1200;
JCONST JDOUBLE Tree::HEIGHT = 700;
