#pragma once
#include "protos/expert/expert_api.grpc.pb.h"

class Expert;

class ExpertService final : public protos::expert::ExpertAPI::Service
{
public:
	ExpertService(Expert* expert);
	~ExpertService();

	grpc::Status ExecuteCommandList(grpc::ServerContext* context, const protos::expert::CommandList* commandList, protos::expert::CommandResultList* commandResultList) override;

private:
	Expert* expert;

};
