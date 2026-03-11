--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type ANS_ToggleWeaponCollision_C
local M = UnLua.Class()

function M:Received_NotifyBegin(MeshComp, Animation, TotalDuration)
    --创建 EActionValidType 类型变量，判断获取的CombatComponent是否有效
    local ValidType = UE.EActionValidType.Valid
    --调用UActionFunctionLibrary的K2_GetPawnCombatComponentFromActor函数，获取CombatComponent
    local CombatComponent = UE.UActionFunctionLibrary.K2_GetPawnCombatComponentFromActor(MeshComp:GetOwner(), ValidType)

    --如果CombatComponent有效，则打印CombatComponent的显示名称
    if ValidType == UE.EActionValidType.Valid then
        local logString = UE.UKismetSystemLibrary.GetDisplayName(CombatComponent)
        
        --拼接一下
        logString = UE.UKismetStringLibrary.Concat_StrStr(logString, " is valid ")
        
        UE.UKismetSystemLibrary.PrintString(none, logString)
        print(logString)
    end
    return true
end

-- function M:Received_NotifyTick(MeshComp, Animation, FrameDeltaTime)
-- end

-- function M:Received_NotifyEnd(MeshComp, Animation)
-- end

return M