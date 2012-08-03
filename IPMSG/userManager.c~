/*!
 * \file	userManager.c
 * \brief	
 * \author	sunshine
 * contact  mxdhlj@163.com
 * \version	0.00
 * \date	11-09-13 19:10:39
 */


#include "userManager.h"

static IPMSG_USE *head=NULL;

/*!
 * \brief 将所有在线用户的信息打印出来
 */
void user_list(void)
{
	IPMSG_USE *pf = head;
	int       id  = 0;
	while(pf != NULL)
	{
		printf("%2d %8s %8s\n", id++, pf->usr_name, pf->host_name);
		pf=pf->next;
	}
}

int find_usr(char *ip)
{
	IPMSG_USE *pf = head;
	while(pf != NULL)
	{
		if((strcmp(pf->usr_ip, ip)) == 0)
			return 1;
		pf=pf->next;
	}
	//printf("not find user!\n");
	return 0;
}

/*!
 * \brief 通过用户输入的ID来确定选择的用户
 *
 * \param id
 *
 * \return 
 */
IPMSG_USE *find_user_byid(int id)
{
	IPMSG_USE *pf=head;
	while(id!=0)
	{
		if(pf->next!=NULL)
			pf=pf->next;
		else
			return NULL;
		id--;
	}
	return pf;
}

/*!
 * \brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 *
 * \param usr
 * \param host
 * \param ip
 *
 * \return 
 */
IPMSG_USE *add_usr(char *usr,char *host,char *ip)
{
	IPMSG_USE *pb,*pf;	

    /*¿¿¿IP¿¿¿¿¿¿¿¿¿¿IP¿*/    
	if(find_usr(ip))
		return NULL;

	pb = (IPMSG_USE*)malloc(sizeof(IPMSG_USE));
	strcpy(pb->usr_name,  usr);
	strcpy(pb->host_name, host);
	strcpy(pb->usr_ip,    ip);

	if(head==NULL)
	{
		head     =pb;
		pb->next =NULL;
		//printf("myself online: [%16s]\n",pb->usr_ip);
	}
	else 
	{	
		IPMSG_USE *pf=head;
        /*¿¿¿¿¿¿¿*/
		while(pf->next != NULL)
			pf=pf->next;
		pf->next = pb;
		//printf("use_name:%s   use_host:%s   use_ip:[%16s]:online !!!\n",pb->usr_name,pb->host_name,pb->usr_ip);
	}
}


/*!
 * \brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 *
 * \param ip
 *
 * \return 
 */
IPMSG_USE *del_usr(char *ip)
{
	IPMSG_USE *pf,*pb;	
	pf = pb = head;
	while((strcmp(pb->usr_ip, ip) != 0)&&(pb->next != NULL))
	{
		pf = pb;
		pb = pb->next;
	}
    /*¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿*/
	if(strcmp(pb->usr_ip, ip) == 0)
	{
        /*¿¿¿¿¿¿¿¿*/
		if(pb==head)
		{
			head=pb->next;
		}
        /*¿¿¿¿¿¿¿¿¿*/
		else
		{
			pf->next=pb->next;
		}	
	
	}	
	if(head != NULL)	
	{
		pf = head;
		printf("list\n");		
		while(pf != NULL)
		{
			pf=pf->next;
		}
	}
}

