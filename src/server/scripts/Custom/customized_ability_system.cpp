/*
Sefiraz - Automatic Spell System
*/

bool CheckSpellTalent01(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM01);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();  
        int32 talentId = field[0].GetInt32();
        

        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 CheckSpellHook01(Player* player, const SpellInfo* info)
{
    /*2 = OnCast
      3 = OnHit
      4 = OnApply
      5 = OnRemove
    */

    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM01);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field   = spell_result->Fetch();
        int32 OnCast   = field[2].GetInt32();
        int32 OnHit    = field[3].GetInt32();
        int32 OnApply  = field[4].GetInt32();
        int32 OnRemove = field[5].GetInt32();

        if (OnCast == 1)
        {
            return 2;
        }
        else if (OnHit == 1)
        {
            return 3;
        }
        else if (OnApply == 1)
        {
            return 4;
        }
        else if (OnRemove == 1)
        {
            return 5;
        }
    }

    return 0;
}

int32 ReturnSpellId01(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM01);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 SpellId = field[1].GetInt32();

        return SpellId;
    }

    return 0;
}

int32 ReturnSpellId1Chance(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM01);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Chance = field[6].GetInt32();

        return Chance;
    }

    return 0;
}

int32 ReturnSpellId1Radius(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM01);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}

bool CheckSpellTalent02(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM02);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 talentId = field[0].GetInt32();


        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 CheckSpellHook02(Player* player, const SpellInfo* info)
{
    /*2 = OnCast
    3 = OnHit
    4 = OnApply
    5 = OnRemove
    */

    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM02);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 OnCast = field[2].GetInt32();
        int32 OnHit = field[3].GetInt32();
        int32 OnApply = field[4].GetInt32();
        int32 OnRemove = field[5].GetInt32();

        if (OnCast == 1)
        {
            return 2;
        }
        else if (OnHit == 1)
        {
            return 3;
        }
        else if (OnApply == 1)
        {
            return 4;
        }
        else if (OnRemove == 1)
        {
            return 5;
        }
    }

    return 0;
}

int32 ReturnSpellId02(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM02);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 SpellId = field[1].GetInt32();

        return SpellId;
    }

    return 0;
}

int32 ReturnSpellId2Chance(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM02);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Chance = field[6].GetInt32();

        return Chance;
    }

    return 0;
}

int32 ReturnSpellId2Radius(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM02);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}


bool CheckSpellTalent03(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM03);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 talentId = field[0].GetInt32();


        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 CheckSpellHook03(Player* player, const SpellInfo* info)
{
    /*2 = OnCast
    3 = OnHit
    4 = OnApply
    5 = OnRemove
    */

    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM03);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 OnCast = field[2].GetInt32();
        int32 OnHit = field[3].GetInt32();
        int32 OnApply = field[4].GetInt32();
        int32 OnRemove = field[5].GetInt32();

        if (OnCast == 1)
        {
            return 2;
        }
        else if (OnHit == 1)
        {
            return 3;
        }
        else if (OnApply == 1)
        {
            return 4;
        }
        else if (OnRemove == 1)
        {
            return 5;
        }
    }

    return 0;
}

int32 ReturnSpellId03(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM03);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 SpellId = field[1].GetInt32();

        return SpellId;
    }

    return 0;
}


int32 ReturnSpellId3Chance(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM03);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Chance = field[6].GetInt32();

        return Chance;
    }

    return 0;
}

int32 ReturnSpellId3Radius(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM03);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}


bool CheckSpellTalent04(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM04);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 talentId = field[0].GetInt32();


        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 CheckSpellHook04(Player* player, const SpellInfo* info)
{
    /*2 = OnCast
    3 = OnHit
    4 = OnApply
    5 = OnRemove
    */

    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM04);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 OnCast = field[2].GetInt32();
        int32 OnHit = field[3].GetInt32();
        int32 OnApply = field[4].GetInt32();
        int32 OnRemove = field[5].GetInt32();

        if (OnCast == 1)
        {
            return 2;
        }
        else if (OnHit == 1)
        {
            return 3;
        }
        else if (OnApply == 1)
        {
            return 4;
        }
        else if (OnRemove == 1)
        {
            return 5;
        }
    }

    return 0;
}

int32 ReturnSpellId04(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM04);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 SpellId = field[1].GetInt32();

        return SpellId;
    }

    return 0;
}


int32 ReturnSpellId4Chance(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM04);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Chance = field[6].GetInt32();

        return Chance;
    }

    return 0;
}


int32 ReturnSpellId4Radius(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM04);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}


bool CheckSpellTalent05(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM05);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 talentId = field[0].GetInt32();


        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 CheckSpellHook05(Player* player, const SpellInfo* info)
{
    /*2 = OnCast
    3 = OnHit
    4 = OnApply
    5 = OnRemove
    */

    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM05);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 OnCast = field[2].GetInt32();
        int32 OnHit = field[3].GetInt32();
        int32 OnApply = field[4].GetInt32();
        int32 OnRemove = field[5].GetInt32();

        if (OnCast == 1)
        {
            return 2;
        }
        else if (OnHit == 1)
        {
            return 3;
        }
        else if (OnApply == 1)
        {
            return 4;
        }
        else if (OnRemove == 1)
        {
            return 5;
        }
    }

    return 0;
}

int32 ReturnSpellId05(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM05);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 SpellId = field[1].GetInt32();

        return SpellId;
    }

    return 0;
}


int32 ReturnSpellId5Chance(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM05);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Chance = field[6].GetInt32();

        return Chance;
    }

    return 0;
}

int32 ReturnSpellId5Radius(Player* player, const SpellInfo* info)
{
    // Next, load any items that were saved
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM05);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}


class spell_automatic_spell_mechanism : public SpellScriptLoader
{
    public:
        spell_automatic_spell_mechanism() : SpellScriptLoader("spell_automatic_spell_mechanism") { }

        class spell_automatic_spell_mechanism_spell_Script : public SpellScript
        {
            PrepareSpellScript(spell_automatic_spell_mechanism_spell_Script);

            void HandleOnHit()
            {
                if (!GetCaster() || GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (!GetHitUnit())
                    return;

                if (GetSpellInfo())
                {
                    // Spell01
                    if (CheckSpellHook01(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook01(GetCaster()->ToPlayer(), GetSpellInfo()) == 3)
                    {
                        if (CheckSpellTalent01(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId1Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId01(GetCaster()->ToPlayer(), GetSpellInfo())))
                                GetCaster()->CastSpell(GetHitUnit(), newInfo->Id, true);
                        }
                    }    

                    // Spell02
                    if (CheckSpellHook02(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook02(GetCaster()->ToPlayer(), GetSpellInfo()) == 3)
                    {
                        if (CheckSpellTalent02(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId2Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId02(GetCaster()->ToPlayer(), GetSpellInfo())))
                                GetCaster()->CastSpell(GetHitUnit(), newInfo->Id, true);
                        }
                    }

                    // Spell03
                    if (CheckSpellHook03(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook03(GetCaster()->ToPlayer(), GetSpellInfo()) == 3)
                    {
                        if (CheckSpellTalent03(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId3Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId03(GetCaster()->ToPlayer(), GetSpellInfo())))
                                GetCaster()->CastSpell(GetHitUnit(), newInfo->Id, true);
                        }
                    }

                    // Spell04
                    if (CheckSpellHook04(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook04(GetCaster()->ToPlayer(), GetSpellInfo()) == 3)
                    {
                        if (CheckSpellTalent04(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId4Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId04(GetCaster()->ToPlayer(), GetSpellInfo())))
                                GetCaster()->CastSpell(GetHitUnit(), newInfo->Id, true);
                        }
                    }

                    // Spell05
                    if (CheckSpellHook05(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook05(GetCaster()->ToPlayer(), GetSpellInfo()) == 3)
                    {
                        if (CheckSpellTalent05(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId5Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId05(GetCaster()->ToPlayer(), GetSpellInfo())))
                                GetCaster()->CastSpell(GetHitUnit(), newInfo->Id, true);
                        }
                    }
                }
            }

            void HandleOnHitAOE()
            {
                /*
                This handles AOE spells, it'll look for players 
                */
               
                if (!GetCaster() || GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return;

                /*
                Spells: 1, 2 - negetive
                Spells: 3,4,5 - friendly
                */

                if (GetSpellInfo())
                {
                    // Spell01
                    if (CheckSpellHook01(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook01(GetCaster()->ToPlayer(), GetSpellInfo()) == 2)
                    {
                        if (CheckSpellTalent01(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId1Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            {
                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId01(GetCaster()->ToPlayer(), GetSpellInfo())))
                                {
                                    UnitList targets;
                                    JadeCore::AnyUnfriendlyUnitInObjectRangeCheck u_check(GetCaster(), GetCaster(), ReturnSpellId1Radius(GetCaster()->ToPlayer(), GetSpellInfo()));
                                    JadeCore::UnitListSearcher<JadeCore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(GetCaster(), targets, u_check);
                                    GetCaster()->VisitNearbyObject(ReturnSpellId1Radius(GetCaster()->ToPlayer(), GetSpellInfo()), searcher);

                                    if (targets.empty())
                                        return;

                                    for (UnitList::iterator iter = targets.begin(); iter != targets.end(); ++iter)
                                    {
                                        GetCaster()->CastSpell((*iter), newInfo->Id, true);
                                    }
                                }
                            }
                        }
                    }

                    // Spell02
                    if (CheckSpellHook02(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook02(GetCaster()->ToPlayer(), GetSpellInfo()) == 2)
                    {
                        if (CheckSpellTalent02(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId2Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            {
                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId02(GetCaster()->ToPlayer(), GetSpellInfo())))
                                {
                                    UnitList targets;
                                    JadeCore::AnyUnfriendlyUnitInObjectRangeCheck u_check(GetCaster(), GetCaster(), ReturnSpellId2Radius(GetCaster()->ToPlayer(), GetSpellInfo()));
                                    JadeCore::UnitListSearcher<JadeCore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(GetCaster(), targets, u_check);
                                    GetCaster()->VisitNearbyObject(ReturnSpellId2Radius(GetCaster()->ToPlayer(), GetSpellInfo()), searcher);

                                    if (targets.empty())
                                        return;

                                    for (UnitList::iterator iter = targets.begin(); iter != targets.end(); ++iter)
                                    {
                                        GetCaster()->CastSpell((*iter), newInfo->Id, true);
                                    }
                                }
                            }
                        }
                    }

                    // Spell03
                    if (CheckSpellHook03(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook03(GetCaster()->ToPlayer(), GetSpellInfo()) == 2)
                    {
                        if (CheckSpellTalent03(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId3Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            {
                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId03(GetCaster()->ToPlayer(), GetSpellInfo())))
                                {
                                    std::list<Player*> listPlayers;
                                    GetCaster()->GetPlayerListInGrid(listPlayers, ReturnSpellId3Radius(GetCaster()->ToPlayer(), GetSpellInfo()));

                                    if (listPlayers.empty())
                                        return;

                                    for (auto itr : listPlayers)
                                    {
                                        GetCaster()->CastSpell(itr, newInfo->Id, true);
                                    }
                                }
                            }
                        }
                    }

                    // Spell04
                    if (CheckSpellHook04(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook04(GetCaster()->ToPlayer(), GetSpellInfo()) == 2)
                    {
                        if (CheckSpellTalent04(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId4Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            {
                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId04(GetCaster()->ToPlayer(), GetSpellInfo())))
                                {
                                    std::list<Player*> listPlayers;
                                    GetCaster()->GetPlayerListInGrid(listPlayers, ReturnSpellId4Radius(GetCaster()->ToPlayer(), GetSpellInfo()));

                                    if (listPlayers.empty())
                                        return;

                                    for (auto itr : listPlayers)
                                    {
                                        GetCaster()->CastSpell(itr, newInfo->Id, true);
                                    }
                                }
                            }
                        }
                    }

                    // Spell05
                    if (CheckSpellHook05(GetCaster()->ToPlayer(), GetSpellInfo()) && CheckSpellHook05(GetCaster()->ToPlayer(), GetSpellInfo()) == 2)
                    {
                        if (CheckSpellTalent05(GetCaster()->ToPlayer(), GetSpellInfo()))
                        {
                            if (roll_chance_i(ReturnSpellId5Chance(GetCaster()->ToPlayer(), GetSpellInfo())))
                            {
                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId05(GetCaster()->ToPlayer(), GetSpellInfo())))
                                {
                                    std::list<Player*> listPlayers;
                                    GetCaster()->GetPlayerListInGrid(listPlayers, ReturnSpellId5Radius(GetCaster()->ToPlayer(), GetSpellInfo()));

                                    if (listPlayers.empty())
                                        return;

                                    for (auto itr : listPlayers)
                                    {
                                        GetCaster()->CastSpell(itr, newInfo->Id, true);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit  += SpellHitFn(spell_automatic_spell_mechanism_spell_Script::HandleOnHit);
                AfterCast  += SpellCastFn(spell_automatic_spell_mechanism_spell_Script::HandleOnHitAOE);
            }

        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_automatic_spell_mechanism_spell_Script();
        }
};

void AddSC_customized_ability_system()
{
    new spell_automatic_spell_mechanism();
}
