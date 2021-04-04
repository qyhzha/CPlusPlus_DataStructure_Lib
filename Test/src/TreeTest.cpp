        BTree<char> gtree;
        BTreeNode<char>* node = NULL;

        gtree.insert('A', NULL);
        node = gtree.find('A');

        gtree.insert('B', node);
        gtree.insert('C', node);
        node = gtree.find('B');

        gtree.insert('D', node);
        gtree.insert('E', node);
        node = gtree.find('C');

        gtree.insert('F', node);
        gtree.insert('G', node);
        node = gtree.find('D');

        gtree.insert('H', node);
        gtree.insert('I', node);
        node = gtree.find('E');

        gtree.insert('J', node);
        gtree.insert('K', node);
        node = gtree.find('F');

        gtree.insert('L', node);
        gtree.insert('M', node);

        std::cout << gtree.count() << std::endl;
        std::cout << gtree.height() << std::endl;
        std::cout << gtree.degree() << std::endl;

        for(gtree.begin(); !gtree.end(); gtree.next())
        {
            std::cout << gtree.current() << " ";
        }

        std::cout << std::endl;

/*        SharedPointer< BTree<char> > tree = gtree.clone();

        for(tree->begin(); !(tree->end()); tree->next())
        {
            std::cout << tree->current() << " ";
        }

        std::cout << std::endl;

        std::cout << (gtree == *tree) << std::endl;*/ 
        
        SharedPointer< LinkList<char> > ret = gtree.traversal(PreOrder);

        for(ret->move(0); !ret->end(); ret->next())
        {
            std::cout << ret->current() << " ";
        }

        std::cout << std::endl;

        ret = gtree.traversal(InOrder);

        for(ret->move(0); !ret->end(); ret->next())
        {
            std::cout << ret->current() << " ";
        }

        std::cout << std::endl;

        ret = gtree.traversal(PostOrder);

        for(ret->move(0); !ret->end(); ret->next())
        {
            std::cout << ret->current() << " ";
        }

        std::cout << std::endl;


        //gtree.clear();

        String str = "ABCDEFGHIJKLM";

        for(int i = 0; i < str.length(); i++)
        {
            TreeNode<char>* node = gtree.find(str[i]);

            while(node)
            {
                std::cout << node->value << " ";

                node = node->parent;
            }

            std::cout << std::endl;
        }