//获取链表共有几个节点
int getListCount(LinkList head)
{
    int len = 0;
    LinkList temp = head->next;
    while (temp != NULL)
    {
        temp = temp->next;
        len++;
    }
    return len;
}

//求链表的中间结点
LNODE *getMidNode(LinkList head)
{
    int len = getListCount(head);
    if (len == 0)
    {
        return NULL;
    }
    LinkList midNode = NULL;
    int midIndex = 0;
    if (len % 2 == 0)
    {
        //链表节点数为偶数
        midIndex = len / 2;
    }
    else
    {
        //链表节点数为奇数
        midIndex = len / 2 + 1;
    }

    int index = 0;
    LinkList temp = head->next;
    while (temp != NULL)
    {
        index++;
        if (index == midIndex)
        {
            midNode = temp;
            cout << "中间节点为:" << midNode->data << endl;
            return midNode;
        }
        temp = temp->next;
    }
    return NULL;
}