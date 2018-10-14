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

//删除链表倒数第 n 个结点
void deleteNth(LinkList &head, int n)
{
    /*
		思路:计算出链表的长度,再根据需要删除倒数第几个节点来算出需要删除的链表节点的index,遍历链表,删除该index处的节点
	*/
    int index = 1;
    int len = getListCount(head);
    if (n <= 0 || n > len)
    {
        cout << "n 有问题" << endl;
        return;
    }

    //待删除节点
    int deleteIndex = len - n + 1;
    LinkList deleteLnode = NULL;
    if (deleteIndex == 1)
    {
        deleteLnode = head->next;
        head->next = head->next->next;
        cout << "已删除节点:" << deleteLnode->data << endl;
        deleteLnode = NULL;
        return;
    }
    cout << "待删除的节点index为:" << deleteIndex << endl;
    LinkList temp = head->next;
    while (temp != NULL)
    {
        //下一个节点就是要删除的节点
        if ((index + 1) == deleteIndex && temp->next != NULL)
        {
            deleteLnode = temp->next;
            temp->next = temp->next->next;
            cout << "已删除节点:" << deleteLnode->data << endl;
            deleteLnode = NULL;
            break;
        }
        temp = temp->next;
        index++;
    }
}