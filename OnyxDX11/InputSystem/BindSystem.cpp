// Copyright (c) 2023 snakEZ
// All rights reserved

#include "BindSystem.h"

BindSystem::BindSystem()
{
}

BindSystem::~BindSystem()
{
}

void BindSystem::CreateBind(InputCommand input_command, int key)
{
    m_binds[input_command] = key;
}

void BindSystem::CreateBind(InputCommand input_command, char key)
{
    m_binds[input_command] = key;
}

void BindSystem::CreateBind(int index_command, char key)
{
    m_binds[index_command] = key;
}

void BindSystem::CreateBind(int index_command, int key)
{
    m_binds[index_command] = key;
}

int BindSystem::GetKeyByCommand(InputCommand input_command)
{
    return m_binds[input_command];
}

BindSystem* BindSystem::Get()
{
    static BindSystem system;
    return &system;
}

void BindSystem::SetBinds(std::map<int, int> binds)
{
    m_binds = binds;
}